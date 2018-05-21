#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// real-world frequencies for each letter
double realFreq[26] = {
	0.0813, // a
	0.0149, // b
	0.0271, // c
	0.0432, // d
	0.1202, // e
	0.0230, // f
	0.0203, // g
	0.0592, // h
	0.0731, // i
	0.0010, // j
	0.0069, // k
	0.0398, // l
	0.0261, // m
	0.0695, // n
	0.0768, // o
	0.0182, // p
	0.0011, // q
	0.0602, // r
	0.0628, // s
	0.0910, // t
	0.0288, // u
	0.0111, // v
	0.0209, // w
	0.0017, // x
	0.0211, // y
	0.0007, // z
};

vector <double> freq;

double d[26][26];

int solCnt;

priority_queue <pair <double, vector <int> > > solutionMappings;

// returns a vector containing a value in range [0; 1] for each letter
// e.g. value 0.2 for letter 'e' means that 0.2*100=20 percent of all letters are 'e'
vector <double> getLetterFrequencies(const string &str) {
	vector <double> freq(26, 0);

	if (str.size() == 0) {
		return freq;
	}

	int letterCount = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			++freq[str[i] - 'a'];
			++letterCount;
		}
	}

	for (int i = 0; i < 26; ++i) {
		freq[i] /= letterCount;
	}

	return freq;
}

// makes all letters lowercase
string normalizeString(const string &str) {
	string res;

	for (int i = 0; i < str.size(); ++i) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			res += (str[i] - 'A' + 'a');
		}
		else {
			res += str[i];
		}
	}
	return res;
}

// decrypts the normalized ciphertext $c, given the monoalphabetic cipher $cipher
// cipher[0] maps to 'a', cipher[1] maps to 'b' ...
string decrypt(const string &c, const vector <int> cipher) {
	string res;
	for (int i = 0; i < c.size(); ++i) {
		if (c[i] >= 'a' && c[i] <= 'z') {
			res += char('a' + cipher[c[i] - 'a']);
		}
		else {
			res += c[i];
		}
	}

	return res;
}

inline double absolute(double val) {
	if (val < 0) return -val;
	return val;
}

void addToAnswer(const vector <int> &mapping, double prob) {
	solutionMappings.push(make_pair(-prob, mapping));
	if (solutionMappings.size() > solCnt) {
		solutionMappings.pop();
	}
}


double globalMaxProb = 0; // initially an impossibly large value

vector <int> letterOrder;

void initLetterOrder(const vector <double> &freq) {
	letterOrder = vector <int> (26);

	vector <pair<double, int> > letterFreqs;

	for (int i = 0; i < freq.size(); ++i) {
		letterFreqs.push_back(make_pair(freq[i], i));
	}

	sort(letterFreqs.begin(), letterFreqs.end());

	for (int i = 0; i < letterFreqs.size(); ++i) {
		letterOrder[i] = letterFreqs[letterFreqs.size() - 1 - i].second;
	}
}

int maxIter = 50000000;

// recursively generates a mapping.
void gen(int letterInd, int mask, double prob, vector <int> &mapping) {
	// cout << letterInd << " " << prob << endl;
	if (letterInd == 26) {
		

		if (prob > globalMaxProb) {
			globalMaxProb = prob;
			addToAnswer(mapping, prob);
		}

		return;
	}

	if (maxIter < 0) {
		return;
	}

	// heuristic to chop off recursion branches which are not likely to yield good results.
	if (prob < globalMaxProb) {
		return;
	}

	--maxIter;

	vector <pair<double, int> > availableLetters;

	int letter = letterOrder[letterInd];

	for (int i = 0; i < 26; ++i) {
		if (mask & (1<<i)) {
			continue;
		}

		double pp = d[letter][i];
		availableLetters.push_back(make_pair(-pp, i));
	}
	sort(availableLetters.begin(), availableLetters.end());

	for (int i = 0; i < availableLetters.size() && i < 3; ++i) {
		mapping[letter] = availableLetters[i].second;

		gen(letterInd + 1, mask | (1 << availableLetters[i].second), 
			prob * (-availableLetters[i].first), mapping);
	}
}

void printMapping(const vector <int> &mapping) {
	vector <int> rev(26);
	for (int i = 0; i < mapping.size(); ++i) {
		rev[mapping[i]] = i;
	}

	cout << "CIPHER: ";
	for (int i = 0; i < rev.size(); ++i) {
		cout << char(rev[i] + 'a');
	}
	cout << endl;
}

void initMappingProbabilities(const vector <double> freq) {
	for (int i = 0; i < 26; ++i) {
		double tempSum = 0;
		double minProb = 1;
		for (int j = 0; j < 26; ++j) {
			d[i][j] = 1 - absolute(freq[i] - realFreq[j]);

			minProb = min(minProb, d[i][j]);
		}

		for (int j = 0; j < 26; ++j) {
			d[i][j] -= minProb;
			tempSum += d[i][j];
		}

		for (int j = 0; j < 26; ++j) {
			d[i][j] /= tempSum;
		}
	}
}

void solve(const vector <double> &freq) {
	initMappingProbabilities(freq);

	initLetterOrder(freq);

	sort(letterOrder.begin(), letterOrder.begin() + 5);

	vector <int> mapping(26, -1);
	gen(0, 0, 1, mapping);
}

int main() {
	string ciphertext;

	cout << "ciphertext: ";

	getline(std::cin, ciphertext);

	if (ciphertext.size() == 0) {
		cerr << "ciphertext cannot be empty.";
		return 1;
	}

	cout << "number of top possible plaintexts: ";

	cin >> solCnt;



	ciphertext = normalizeString(ciphertext);
	freq = getLetterFrequencies(ciphertext);
	
	solve(freq);


	solCnt = solutionMappings.size();

	while (!solutionMappings.empty()) {
		cout << solCnt-- << endl;
		printMapping(solutionMappings.top().second);
		cout << "PLAINTEXT: " << decrypt(ciphertext, solutionMappings.top().second) << endl << endl;
		solutionMappings.pop();
	}


	return 0;
}


/*

zfljyh mfb qxn chzxofu cfjbjyl lcfojaq. ybfajfeuh nyghcbaxxg xc hrwchbbjxy gjbbjzjufc bx bniijdjhya. ab wfcaq hohcq khfcg fyg hohya lfq. gojdh kh jyghhg akjylb fgjhnb jy ynzehc bx nyhfbq. x zfyq ixnc ifda jy kh ifju. q knyl ja vnja yhra gx xi. a ijiahhy dkfczhg eq wcjofah bfojylb ja zc. foxncfeuh dnuajofahg fuahcfajxy hyachfajhb qha zha bqzwfakjph. ncyjanch ixcihjahg bjc xeshdajxy wna dxcgjfuuq dxyajynhg bwxcabzhy.fy chvnhba fgfwahg bwjcjab bha wchbbhg. w ax ghyxajyl bneshdab bhybjeuh ihhujylb ja jygnulhg gjchdauq. h gmhuujyl huhlfydh gx bknaahcb fwwhajah qxncbhui gjohcahg. nc yhra gchm zndk qxn mjak cfyt. xch zfyq khug flh kxug cxbh akfy xnc. kh ujahcfanch bhyajzhyab fyq dxyacfbahg. ha fmfch sxq bhybh qxnyl yxm ahfcb dkjyf bkq. ymjuujyl bwxcabzhy kh jy vnhbajxyb bhwahzehc akhchixch ghbdcjehg bx. aafdtb zfq bha ihm ehujhoh zxzhyab mfb. hfbxyfeuq kxm wxbbhbbjxy bkq mfq jyacxgndhg flh jyvnjhangh. jbbhg kh hylflh yx hrhahc xi. ajuu acjhg zhfyb mh fmfch xcghc fzxyl xy. ughba ifakhc dfy ghbjly afbahb gjg sxq bhaauh. xnbhg inanch kh qh fy zfcthg. cxbh zc cfwjg jy bx ohrhg mxcgb. fq mhudxzh uhg fgg ufbajyl dkjhiuq bfq uxxtjyl. fq jygnulhydh gjiijdnuaq kfz dfy wna hbwhdjfuuq. cjyljyl chzhzehc ixc bnwwujhg khc mkq mfb dxyijyhg. jgguhaxy wcjydjwuh gjg bkh wcxdncjyl hrahybjoh ehujhojyl fgg. hfakhc fgfwahg wchwfch xk jb dfuujyl. khbh mcxyl xi kh mkjdk akhch bzjuh ax zq icxya. h icnja xk hysxq ja xi mkxbh afeuh. nuajofahg xddfbjxyfu xug khc nywuhfbjyl nywuhfbfya. a fb gx eh flfjyba wfbanch dxohchg ojhmjyl bafcahg. ysxqhg zh bhaauhg zc chbwhda yx bwjcjab djojuuq. ejujajhb ixcihjahg bjanfajxy hrachzhuq zq ax kh chbhzeuhg. ug kfg dxyojdajxy gjbdchajxy nyghcbaxxg wna wcjydjwuhb qxn. fadk zhfyb thhwb cxnyg xyh khc vnjdt. kh ixczjyl amx dxzixca jyojahg. ha bkh jydxzh hiihda hgmfcg. yajch ghbjch mfq ghbjly ihm. cb bhyajzhyab uhg bxujdjangh hbajzfajyl icjhygbkjw ifa. hfya akxbh hohya jb mhhtb bafah ja ax xc. xq ena kfb ixuuq dkfcz akhch jab. ab ifda ahy bwxa gchm. y xy fyyxnydjyl ji xi dxzwfcjbxy wjfyxixcah wcxshdajxy. fjgb kxwhg lfq qha ehg fbthg eujyg gcjhg wxjya. y fecxfg gfylhc ujthuq chlcha amhyaq hgmfcg gx. xx kxccjeuh dxybjghc ixuuxmhg zfq gjiihchg flh. y chba ji zxch ijoh zc xi. lh snba khc cfyt zha gxmy mfq. aahyghg chvnjchg bx jy dkhhcinu fy. xzhbajd chwuqjyl bkh chbxuohg kjz ixc gjg. fakhc jy ufbahg yx mjakjy yx. foh chfg nbh mfq zfth bwxa kxm yxc. y gfnlkahc lxxgyhbb fy ujthmjbh xk dxybjghc fa wcxdnchg mfyghchg. xylb mxcgb mcxyl eq zh kjuub khfcg ajzhg. fwwq hfa zfq gxxcb bxylb. h jlyxcfya bx xi bnjafeuh gjbbnfgh mhggjylb axlhakhc. hfba mkxuh ajzhg mh jb. y bzfuuyhbb ghijdjhya gjbdxncbh gx yhmbwfwhc eh fy hflhcyhbb dxyajynhg. c zq chfgq lnhba qh fiahc bkxca fa. ykfejajyl gjbdchajxy akh khc gjbwfadkhg ghdjbjohuq exjbahcxnb sxq. x ixcz mhch mjbk xwhy jb feuh xi zjuh xi. fjajyl hrwchbb ji wchohya ja mh fy znbjdfu. bwhdjfuuq chfbxyfeuh acfohuujyl bkh bxy. hbxncdhb chbhzeuhg ixcihjahg yx ax phfuxnbuq. fb wcxdnchg gfnlkahc kxm icjhyguq ixuuxmhg chwhfahg mkx bncwcjbh. chfa fbthg xk nyghc xy oxjdh gxmyb. fm axlhakhc wcxbwhda tjygyhbb bhdncjyl bjr. hfcyjyl mkq lha kfbahyhg bzfuuhba dkhhcinu. hwfca gx eh bx kh hyxnlk afuhya. xdjfeuh ixczhcuq bjr ena kfygbxzh. w gx ojhm ajzh akhq bkxa. h dxydunghg gjbwxbjyl wcxojbjxy eq vnhbajxyb fb bjanfajxy. ab hbajzfajyl fch zxajxyuhbb gfq bhyajzhyab hyg. fuujyl fy jzfljyh fa ixcefgh. a yfzh yx fy mkfa ujth bwxa. chbbhg zq eq gx fiijrhg kh bangjhg. janfajxy fgzjaajyl wcxzxajxy fa xc ax whcdhjohg eh. c fdnahyhbb mh fb hbajzfeuh hysxqzhya nw. y khug ufah fb ihua tyxm. hfcy gx fuuxm bxujg ax lcfoh. jgguhaxy bnbwjdjxy flh khc faahyajxy. kjhiuq bhohcfu ehg jab mjbkjyl. b bx zxzhyab xy dkfzehc wchbbhg ax. xneainu qha mfq wcxwhcuq fybmhchg knzfyjaq jab ghbjcxnb. jynahc ehujhoh bhcojdh fccjohg djojuuq fgg fuu. dnahyhbb fuuxmfydh fy fa hflhcyhbb ifoxncjah jy hrahybjoh hrvnjbjah qh. exydhcyb lchfahba zfclfcha kjz febxunah hyacfydh yfq. nxxc yhfa mhht gx ijyg wfba kh. jh yx bncwcjbh kh kxyxnchg jygnulhg. wywfdthg hyghfoxc bjr bahhwhba kfg knbefygb khc. bfjyahg yx xc fiijrhg ja bx djojuuq. grwxbhg yhjakhc wchbbhg bx dxaaflh fb wcxdhhg fa xiijdhb. zfq akhq lxyh bjc lfzh ixnc. hfoxncfeuh wjfyxixcah xk zxajxyuhbb hrdhuuhydh xi fbaxyjbkhg mh wcjydjwuhb. ofccfya wchbhya lfcchab ujzjahg dxcgjfu jy jyvnjcq ax. fnwwxcahg zh bmhhayhbb ehkfojxnc bkfzhuhbb hrdhuuhya bx fccfyljyl. uuxm zjuhb mxnyg wufdh akh uhfoh kfg. xx bjaajyl bneshda yx jzwcxoh bangjhg ujzjahg. rh jygnulhydh nychbhcohg dxyyhdajxy fuahcfajxy fwwhfcfydh zq fy fbaxyjbkhg. ww fb bhhy bhya zfth kh akhq xi. ihc cfjbjyl fyg kjzbhui wfbanch ehujhoh ihzfuhb. hfydq bkh banii fiahc fmfch zhcja bzfuu kjb. ekfczhg hbahhzb undtjuq flh xna. grachzhuq mh wcxzxajxy chzfjyghc hflhcyhbb hysxqzhya fy. ifz khc ghzfygb chzxofu ecxnlka zjynahc cfjbjyl jyojahg lfq. exyahyahg dxybjbahg dxyajynfu dncjxbjaq dxyafjyhg lha bhr. hxcak dkjug gcjhg jy jy fmfch gx. rxn kfg zha akhq bxyl kxm ihhu ufjy hoju yhfc. fzfuu bkh foxjg bjr qha afeuh dkjyf. yg ehg zfth bfq ehhy akhy gjyh zcb. xx kxnbhkxug cfwancxnb inuijuuhg faahzwahg xy bx. ocxah mfahc mxzfy xi khfca ja axafu xakhc. jq jy hyajchuq bhdncjyl bnjafeuh lcfdhinu fa ifzjujhb jzwcxohg. qhfuxnbuq ihm incyjanch chwnubjoh mfb flchhfeuh dxybjbahg gjiijdnua. exuuhdahg echftifba hbajzfeuh vnhbajxyb jy ax ifoxncjah ja. vyxmy kh wufdh mxcak mxcgb ja fb ax. fwxth yxm yxjbh xii bzfca khc chfgq. fngghy bkh bhhjyl lfccha ifc chlfcg. jq kfcguq ja gjchda ji wchaaq nw chlcha. ejujaq akxnlka hyvnjch bhaauhg wcnghya qxn bjc. yc hfbq tyhm bxug xy mhuu dxzh qhfc. fxzhakjyl dxybnuahg flh hrachzhuq hyg wcxdncjyl. exuuhdajyl wchihchydh kh jyvnjhangh wcxshdajxy zh jy eq. fx gx xi bniijdjhya wcxshdajyl fy akxcxnlkuq nydxzzxyuq wcxbwhcxnb dxyojdajxy. bjfyxixcah wcjydjwuhb xnc nyfiihdahg yxa ixc fbaxyjbkhg acfohuujyl fch wfcajdnufc. exybjghchg gjbdxohchg qh bhyajzhyab wcxshdajyl hyachfajhb xi zhufydkxuq jb. cy hrwchbbjxy fy bxujdjangh wcjydjwuhb jy gx. ifcg gx zh bjlk mjak mhba bfzh ufgq. xkhjc bfohg ujyhy gxmyb ahfcb bxy fgg znbjd. grwchbbjxy fuahcfajxy hyachfajhb zcb dfy ahczjyfahg hbajzfajyl. ihc axx fgg yfccxm kfojyl mjbkhg. xx akjylb bx ghyjhg fgzjch. z mxnyg mxcak mfahc kh ujyhy fa ohrhg. zhfa xmy yxc bkh bfjg bhh mfut. yg dkfcz fgg lchhy qxn akhbh. ffyl enbq jy akjb gchm qh ijyh. a lchfahc wchwfch znbjdfu bx faafdtb fb xy gjbafya. czwcxojyl flh xnc khc dxcgjfuuq jyahyajxy. ijb ghoxybkjch bniijdjhya wchdfnajxy bfq wchihchydh zjgguhaxyb jybjwjgjaq. fjydh zjlka mfahc khydh akh khc mxcbh. exydunghg ja xiihygjyl ghshdajxy gx hfcyhbauq fb zh gjchdajxy. zfanch wufqhg akjcaq fuu kjz. zfzh mhch mh fa kxwh. shzfjyghc kxnbhkxug gjchdajxy phfuxnbuq akh nymjuujyl ehg bhr. txbh fyg lfq kfz bfth zha akfa. faxxg khc wufdh xyh ahy bwxth qha. ihfg dfbh tyhm hohc bha mkq xohc. ufcjfyyh chancyhg xi whdnujfc chwuqjyl jy zxghcfah. sxnbhg lha hyfeuh lfccha hbafah xug dxnyaq. gyachfajhb qxn ghoxybkjch ufm gjbbjzjufc ahczjyfahg. fnwwxbh hyg lha exq mfccfya lhyhcfu yfancfu. nhujlkainu zha bniijdjhya wcxshdajxy fbt. nhdjbjohuq hohcqakjyl wcjydjwuhb ji wchihchydh gx jzwchbbjxy xi. bchbhcohg xk bx gjiijdnua chwnubjoh xy jy kxnbhkxug. cy mkfa gx zjbb ajzh eh. kfuuhq fb eh fwwhfc dfyyxa bx eq. exyojydhg chbhzeuhg ghwhyghya chzfjyghc uhg phfuxnbuq kjb bkq xmy ehuxyljyl. umfqb uhylak uhaahc fgjhnb fgg ynzehc zxzhya bkh. bcxzjbh ihm dxzwfbb bjr bhohcfu xug xiijdhb chzxofu wfcajhb ifa. exydunghg cfwancxnb ja jyahyajxy whcihdauq gfnlkahcb jb fb. ih xwwxbh fa akcxmy ghbjch xi yx. yyxnydjyl jzwchbbjxy nyfiihdahg gfq kjb fch nychbhcohg jygnulhydh. ijz kfcg ijyg chfg fch qxn bfyl. bfcuxcb ojbjahg yxjbjhc kxm hrwufjy wuhfbhg kjb bhh bnwwxbh. nx fbkfzhg fbbnchg xy chufahg xiihydh fa hvnfuuq axafuuq. wbh zjuh khc mkxz akhq jab. vhwa kxug fy mfya fb kh echg xi. ofb gfbkmxxg ufyguxcg dkhhcinu knbefygb amx. gbafah mkq akhjcb jyghhg kjz wxujah xug bhaauh akxnlk bkh. cy fb fa chlfcg hfbjuq yfccxm cxnbhg fgjhnb.

*/