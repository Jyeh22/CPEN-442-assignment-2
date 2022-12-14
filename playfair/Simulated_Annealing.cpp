#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <unordered_map>
#include <thread>
#include <set>

#define ROWS 5
#define COLS 5
#define SKIP 'J'
#define TEMP 0.15
#define COOL_STEP 1000
#define LOG_STEP 1000
// #define PLATEAU_RESET_STEP 500000000
#define COOL_RATIO 0.99
#define MAX_STEP 5000000
#define EPOCHS 2
#define KEYLEN 25

std::string cipher;
std::unordered_map<std::string, float> quad;
std::unordered_map<std::string, float> cache;
std::set<std::string> correct_keys;

std::string simulated_annealing();
std::string rand_modify(std::string);
void swap_letters(std::string &);
void swap_cols(std::string &);
void swap_rows(std::string &);
void rev_col(std::string &);
void rev_row(std::string &);
void rev(std::string &);
float fitness(std::string);
std::string decode(std::string);

int main(){
    cipher = "VNYDTRMVPHHXECXPNHDQYRNXATTMHLOUVNNZFNMPMCUKMVUVYDEXLSMSHXQZDRRAXLSGMVTLHNXWTMHLPHIVCEHNMVTLLVMSHXYIMPNTPLHRGHHRGXRFIFXVVUBHLZWMATLSAPEMZUFNWHRUFVBTRXITVQSLHNYIVLGOOXGMHNTHNFLCHNVPEPHPBHDQYRNXATPVATFPDHHNHIMSAYPUZMDNMCZUTHAYMVTBYDRCAIVPOXBKFXVERMMHUVXINKHNYRXGVLLSPVQDOQNGMPEMSTXRAXFTHPYDNGYDLCRXGMGAYPXPPDLFNXATNFXEHNQRCLIHLENGTMYXYDMHYDVQLZOHDQYIFNOXVHWRSXGOVQHIWFYTHPPHAPNTZTQRVLDHNGHNHVYDATHDWHZNVQTMHXHWSXHNOXBKMKXEXEZNKNEVFTLZWMATPYFCFUHRGMHNTHPMIHXEXEMHTSZXMYTHTASXHNMCUKVLOXPMNTHGYDKFZNCUTHAYMVTBYDWMATPQWHGZHQTMHXHCAINFOHRDKOTMYXYDMHYDQCFNPHVHOXMAQYHRYLNXATTHACNKLZWMATURDRPNVPEBLVXQLZWMATLSPRHNSXTDPMMCVUFUHTOKXLXOTATMFNTMDZVHOXGMHNUVRQGLGXUMUXGLFOFCPVHNYRLVUZRCNKHVSXTDLZWMATNFXEHNQRCLIHLENGYDGXSGVUFUGAUPHRATOHNGMYZBNXATYDUVTATMLZWMATNFXEHNDVHNVPLZWMATTMEXSFMPHRPLDIDHUXHNEMXHNGHNQRCLIHLFCLPRDHIHMSHDAEUVCLAHNGYDLZAVRUDRYLNXATTMQOHPIHIKNZTHCAFOPMFBLZWMATMYVPDQSXLSMSHXDHNGYDTMHYUVRLRVOHVNNZCRPHCICAPQHLMCHCOHRDAKIHCANZDHNGXEXEZNGAUPHPZGDHQVVPPHHGEMZUCHOXKNVXPARVHGZXCATFAKVPHNHIOXBKMKWHRQHPXZXFHONGGNWFNHYDPLSXOHLZWMATTMEXMCUKVLRYHGNVHTDZMHNTBGXGDHNGMPMCNFGXVHCDRXRQGNRDLHLZWMATLSPRNTHONGEMOTGNHNMVGSRFNXATNTIROTPYHVATHDUFAYCAMPGAYIEMRDPYLSPVOXHATMZBLVUZTMOXHNVPPWLEUKRDUXMHNGYDLZAVRUDRYLNXATKWHTOUVNNZFNHNDQNFUWHPYDQCRDMCMCHCTLMVLZWMATHNMVPUOTXUFNTAMSAYPUMTOHHNUVGRHRVQHXHROHATHDIHRQDRHNTHXUFNSFMPHRVMITVLHTMHEVFVNZOXBKHCOHYZTMXGYLLVUCRDMZHRAIYRNXATTMHLAKVPGXSGMVTLHAYRCLQRXFCDYDEVLFYDQXGVMAQZDNXFHDLCOHNFXEXUNZHDPRAKNTKACLIHAPDNXKNHGNLSXGIHMVHNUVFAIWZQATOMVHLENGTMZBLVXZKUHVVQLZXFQODIHPNTBHSXCLDVOAQZKMLURQYXMPQNPACMOXGMHNHVYDDNGIEVOLOXMZTHWHRQHPTMHLPHCAAGYDLZAVYDMCMHDHOXGMHNDVHNVPPWLEZFNXATVQVROTYDMCVZNGNTAIDHYZIHLZWMATFCIHGNHRGMHNYRVLMHXLZLNXATVNMVFNDNAPPMIHHNVPYIFNLTPVTHRAZLGSAKYDATGZMKIHOXPMRQAGNFHLGMHNUVLZWMATLSPRKNDNIYEXMCVZNGUFAYLTXLXOZFCLYRLVMCAKVPCACGMKHNDVGOFLZXLZUAVLPHHXYRNXATNFEWOTLZWMATURDZXSOAQYLHPCRMZVMVDZIFYDLHDZIUSXGOPYFNDXXOTATMFNTMDZAKYDWANXATTMHLPYGMPHAITMHNTMVNIHSLHNHIOXBKLCMVNFPVHNDVOAHBEMOTZUVLHNNTIROTMVHNUVXZLAYLNXATZNATGMPHCIYDHNVPNZVRNFFLZXVLTATMOXHTAKVPHNYRLVUZNTODNZVRHNSXTDGMHNUVNOVPLZWMATTMOLHDRWHDEXXZXFHGCENTLEGNPDKNNXYPLCMVOQNGYZDXXOFXFBDZWFTAHRGXOTTMEGXFRDHXDVLUAKYDNKFTYRNXATTMQLLVWUNTBHSXNFEWTAUFPVHNDPPVTHNSUXGLGDRIHIYPLCMVNFOUVNNZFNIYPDGMGNHNDIHIVPCAYLMPQHNGMEVGQVZLNXATNFXEOXLVHNQDCLVHNKCDLZWMATVUZADQSXVQHITMMXSXNKNDRNHPYDXHNGNDLZWMATQDVUTATMMXSXZFNXATPVKMAVDHHNQVFCPVFLZXOXPMPMOUUFAYTMMSLZUAVLHTGCQRDIDRMVTBSGZNXZVHUVCRXLXGOXBMDRAFNXATNFXEHNDPRPAFNXATRDKMOKXONGTMQOYDNTOHDHHNYPFNPQGMGNHNQVFCPVFLZXOXGMHNVPYIVPHVSLHVRYNFHTGLCGHBYDLVLHVUHDZNCBNXATTMHGYDACOHMCVFSXTDTMQXMHXRRDOL";
    assert(cipher.length() % 2 == 0);
    // std::cout << decode("GTBKPDHYQEONZSVXMWUILACFR") << std::endl;

    std::string line;
    std::ifstream myfile ("english_quadgrams.txt");
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            std::size_t found = line.find(SKIP);
            if (found == std::string::npos){
                float log_count;
                std::stringstream sstream(line.substr(5));
                sstream >> log_count;
                log_count = log(log_count);
                quad[line.substr(0, 4)] = log_count;
            }
        }
        myfile.close();
    }
    std::cout.precision(3);
    simulated_annealing();
    return 0;
}

std::string simulated_annealing(){
    float new_score, saved_score, best_score = -100.0;
    float dF, prob;
    std::string plain, new_key, best_key, saved_key = "ABCDEFGHIKLMNOPQRSTUVWXYZ", epoch_best_key;
    for (int epoch = 0; epoch < EPOCHS; epoch++){
        size_t plateau_timer = 0;
        float epoch_best_score = -100.0, T = TEMP;
        std::random_shuffle(saved_key.begin(), saved_key.end());
        saved_score = fitness(saved_key);

        for (int step = 1; step < MAX_STEP + 1; step++) {
            // randomly modify key
            new_key = rand_modify(saved_key);
            new_score = fitness(new_key);

            dF = new_score - saved_score;
            // If the fitness score of the new key is better, save the new key
            // If the new key has a lower score, still give it a exp(dF/T) chance to be saved
            // This is the difference from simple hill-climbing method. It allows unfit children to live in order to escape local optima.
            if (dF >= 0){
                saved_score = new_score;
                saved_key = new_key;
            }else{
                prob = exp(dF/T);
                if(prob > 1.0 * rand() / RAND_MAX){
                    saved_score = new_score;
                    saved_key = new_key;     
                }
            }
            if (saved_score > epoch_best_score){
                epoch_best_score = saved_score;
                epoch_best_key = saved_key;
                plateau_timer = 0;
            }
            plateau_timer += 1;
            // if (plateau_timer == PLATEAU_RESET_STEP) break;
            if (step % COOL_STEP == 0) T *= COOL_RATIO;
            if (step % LOG_STEP == 0) std::cout << std::fixed << "Epoch:" << epoch << " " << step / (float)MAX_STEP * 100 << "%, best:" << best_score << ", epoch best: " << epoch_best_score << ", T:" << T  << ", saved_score:" << saved_score << ", key:" << epoch_best_key << std::endl;
        }
        if (epoch_best_score > best_score){
            best_score = epoch_best_score;
            best_key = epoch_best_key;
        }
        // // Given that we already found the correct plaintext, save all plausible keys.
        // if (plain == "SOHEPAINTEDMYRIGHTEYECOMMAANDASXSOONASITWASFINISHEDIFOUNDMYSELFLOXOKINGATHIMANDATEVERYTHINGAROUNDMEWITHAGREATDEALOFCURIOSITYCOMXMAFORTHISWASMYFIRSTGLIMPSEOFTHEWORLDDOTXTHATSARATHERPRETTYEYECOMMAREMARKEDTHEMUNCHKINWHOWASWATCHINGTHEFARMERDOTBLUEPAINTISIUSTTHECOLORFOREYESDOTITHINKILLMAKETHEOTHERALITXTLEBIGGERCOMMASAIDTHEFARMERDOTANDWHENTHESECONDEYEWASDONEICOULDSEEMUCHBETTERTHANBEFOREDOTTHENHEMADEMYNOSEANDMYMOUTHDOTBUTIDIDNOTSPEAKCOMXMABECAUSEATXTHATTIMEIDIDNTKNOWWHATAMOUTHWASFORDOTIHADTHEFUNOFWATCHINGTHEMXMAKEMYBODYANDMYARMSANDLEGSANDWHENTHEYFASTENEDONMYHEADCOMMAATLASTCOMXMAIFELTVERYPROUDCOMXMAFORITHOUGHTIWASIUSTASGOXODAMANASANYONEDOTXTHISFELXLOWXWILXLSCARETHECROWSFASTENOUGHCOMXMASAIDTHEFARMERDOTHELOOKSIUSTLIKEAMANDOTWHYCOMMAHEISAMANCOMXMASAIDTHEOTHERCOMXMAANDIQUITEAGREXEDWITHHIMDOTTHEFARMERCARRIEDMEUNDERHISARMTOTHECORNFIELDCOMMAANDSETMEUPONATALLSTICKCOMXMAWHEREYOUFOUNDMEDOTHEANDHISFRIENDSOONAFTERWALKEDAWAYANDLEFTMEALONEDOTIDIDNOTLIKETOBEDESERTEDTHISWAYDOTSOITRIEDTOWALKAFTERTHEMDOTBUTMYFEETWOULDNOTTOUCHTHEGROUNDCOMXMAANDIWASFORCEDTOSTAYONTHATPOLEDOTITWASALONELYLIFETOLEADCOMXMAFORIHADNOTHINGTOTHINKOFCOMMAHAVINGBEENMADESUCHALITTLEWHILEBEFOREDOTMANYCROWSANDOTHERBIRDSFLEWINTOTHECORNFIELDCOMMABUTASXSOONASTHEYSAWMETHEYFLEWAWAYAGAINCOMXMATHINKINGIWASAMUNCHKINANDTHISPLEASEDMEANDMADEMEFEELTHATIWASQUITEANIMPORTANTPERSONDOTBYANDBYANOLDCROWFLEWNEARMECOMMAANDAFTERLOOKINGATMECAREFULLYHEPERCHEDUPONMYSHOULDERANDSAIDIWONDERIFTHATFARMERTHOUGHTTOFOOLMEINTHISCLUMSYMANXNERDOTANYCROWOFSENSECOULDSEXETHATYOUAREONLYSTUFXFEDWITHSTRAWDOTXTHENHEHOPXPEDXDOWNATMYFEETANDATEALLTHECORNHEWANTEDDOTXTHEOTHERBIRDSCOMMASEEINGHEWASNOTHARMEDBYMECOMXMACAMETOEATXTHECORNTOXOCOMMASOINASHORTTIMETHEREWASAGREATFLOCKOFTHEMABOUTMEDOTIFELTSADATXTHISCOMXMAFORITSHOWEDIWASNOTSUCHAGOXODSCARECROWAFTERALLBUTTHEOLDCROWCOMFORTEDMECOMMASAYINGCOMXMAIFYOUONLYHADBRAINSINYOURHEADYOUWOULDBEASGOODAMANASANYOFTHEMCOMMAANDABETXTERMANTHANSOMEOFTHEMDOTBRAINSARETHEONLYTHINGSWORTHHAVINGINTHISWORLDCOMMANOMATXTERWHETHERONEISACROWORAMANDOTAFTERTHECROWSHADGONEITHOUGHTXTHISOVERCOMXMAANDXDECIDEDIWOULDTRYHARDTOGETSOMEBRAINSDOTBYGOODLUCKYOUCAMEALONGANDPULLEDMEOFXFTHESTAKECOMMAANDFROMWHATYOUSAYIAMSURETHEGREATOZWILXLGIVEMEBRAINSASXSOONASWEGETXTOTHEXEMERALDCITYDOTIHOPESOCOMMASAIDDOROTHYEARNESTLYCOMXMASINCEYOUSEEMANXIOUSTOHAVETHEMDOTOHCOMXMAYESIAMANXIOUSCOMMARETURNEDTHESCARECROWDOTITISXSUCHANUNCOMFORTABLEFEXELINGTOKNOWONEISAFOXOLDOTWELLCOMMASAIDTHEGIRLCOMMALETUSGODOTANDSHEHANDEDTHEBASKETXTOTHESCARECROWDOTXTHEREWERENOFENCESATALXLBYTHEROADSIDENOWCOMMAANDTHELANDWASROUGHANDUNTILLEDX"){
        //     correct_keys.insert(epoch_best_key);
        // }
        std::cout << "key:" << epoch_best_key << ", score:" << epoch_best_score << std::endl;
    }
    // std::cout << "\n====================\nAll possible keys:\n====================" << std::endl;
    // for (std::set<std::string>::iterator it=correct_keys.begin(); it!=correct_keys.end(); ++it)
    //     std::cout << *it << std::endl;

    plain = decode(best_key);
    std::cout << "\nplaintext:" << plain << std::endl;
    std::cout << "key:" << best_key << ", score:" << best_score << std::endl;
    return plain;
}

std::string rand_modify(std::string key){
    size_t r = rand() % 50;
    std::string new_key = key;
    // assign random modifications to the keys. Most of which is simply swaping two letters
    switch (r)
    {
    case 0:
        swap_cols(new_key); // swap 2 columns at random
        break;
    case 1:
        swap_rows(new_key); // swap 2 rows at random
        break;
    case 2:
        rev_col(new_key); // reverse a random column
        break;
    case 3:
        rev_row(new_key); // reverse a random row
        break;
    case 4:
        rev(new_key); // reverse the key
        break;
    default:
        swap_letters(new_key); // randomly swap 2 letters
        break;
    }
    return new_key;
}

// measure fitness of a key based on quadgram frequency of the decoded plaintext
// Reference: http://practicalcryptography.com/cryptanalysis/text-characterisation/quadgrams/
float fitness(std::string key){
    // cache results so we don't repeat calculations
    if (cache.find(key) != cache.end()){
        return cache[key];
    }
    std::string plain = decode(key);
    float score = 0;
    for (int i = 0; i < plain.length() - 3; i++) {
        score += quad[plain.substr(i, 4)];
    }
    score /= (cipher.length() - 3);
    cache[key] = score;
    return score;
}

void swap_letters(std::string &key){
    size_t a = rand() % KEYLEN;
    size_t b = rand() % KEYLEN;
    char temp = key[a];
    key[a] = key[b];
    key[b] = temp;
}

void swap_cols(std::string &key){
    size_t a = rand() % COLS;
    size_t b = rand() % COLS;
    char c;
    for (int i=0; i < ROWS; i++) {
        c = key[ i * COLS + a ];
        key[ i * COLS + a ] = key[ i * COLS + b ];
        key[ i * COLS + b ] = c;
    }
}

void swap_rows(std::string &key){
    size_t a = rand() % ROWS;
    size_t b = rand() % ROWS;
    char c;
    for (int i=0; i < COLS; i++) {
        c = key[ a * COLS + i ];
        key[ a * COLS + i ] = key[ b * COLS + i ];
        key[ b * COLS + i ] = c;
    }
}

void rev_col(std::string &key){
    size_t a = rand() % COLS;
    char c;
    for (int i=0; i < ROWS / 2; i++) {
        c = key[ i * ROWS + a ];
        key[ i * COLS + a ] = key[ (ROWS - i - 1) * COLS + a ];
        key[ (ROWS - i - 1) * COLS + a ] = c;
    }
}

void rev_row(std::string &key){
    size_t a = rand() % ROWS;
    char c;
    for (int i=0; i < COLS / 2; i++) {
        c = key[ a * COLS + i ];
        key[ a * COLS + i ] = key[ a * COLS + (ROWS - i - 1) ];
        key[ a * COLS + (ROWS - i - 1) ] = c;
    }
}

void rev(std::string &key){
    char c;
    for (int i=0; i < KEYLEN / 2; i++) {
        c = key[i];
        key[i] = key[KEYLEN - i - 1];
        key[KEYLEN - i - 1] = c;
    }
}

std::string decode(std::string key){
    char a, b;
    int ia, ib, ic, id;
    int ca[2], cb[2];
    std::string plain;
    for (int i = 0; i < cipher.length(); i += 2){
        a = cipher[i];
        b = cipher[i+1];
        ia = key.find(a);
        ib = key.find(b);
        ca[0] = ia / COLS;
        ca[1] = ia % COLS;
        cb[0] = ib / COLS;
        cb[1] = ib % COLS;
        if (ca[0] == cb[0]){
            ic = ca[0] * COLS + (ca[1] + (COLS - 1)) % COLS;
            id = cb[0] * COLS + (cb[1] + (COLS - 1)) % COLS;
        }else if (ca[1] == cb[1]){
            ic = ((ca[0] + (COLS - 1)) % ROWS ) * COLS + ca[1];
            id = ((cb[0] + (COLS - 1)) % ROWS ) * COLS + ca[1];
        }else {
            ic = ca[0] * COLS + cb[1];
            id = cb[0] * COLS + ca[1];
        }
        plain += key[ic];
        plain += key[id];
    }
    return plain;
}

// References: http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-playfair/
//              http://practicalcryptography.com/cryptanalysis/text-characterisation/quadgrams/