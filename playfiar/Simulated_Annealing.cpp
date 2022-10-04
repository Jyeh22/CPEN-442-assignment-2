#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <unordered_map>

#define ROWS 5
#define COLS 5
#define SKIP 'J'
#define TEMP 1.0
#define COOL_STEP 1000
#define LOG_STEP 1000
#define RESET_STEP 100000
#define COOL_RATIO 0.95
#define MAX_STEP 1000000
#define KEYLEN ROWS*COLS

std::string cipher;

std::unordered_map<std::string, float> quad;

std::string simulated_annealing();
std::string rand_modify(std::string);
void swap_letters(std::string &);
void swap_cols(std::string &);
void swap_rows(std::string &);
void rev_col(std::string &);
void rev_row(std::string &);
float fitness(std::string);
std::string decode(std::string);

int main(){
    // std::string key = "MONARCHYBDEFGIKLPQSTUVWXZ";
    cipher = "VNYDTRMVPHHXECXPNHDQYRNXATTMHLOUVNNZFNMPMCUKMVUVYDEXLSMSHXQZDRRAXLSGMVTLHNXWTMHLPHIVCEHNMVTLLVMSHXYIMPNTPLHRGHHRGXRFIFXVVUBHLZWMATLSAPEMZUFNWHRUFVBTRXITVQSLHNYIVLGOOXGMHNTHNFLCHNVPEPHPBHDQYRNXATPVATFPDHHNHIMSAYPUZMDNMCZUTHAYMVTBYDRCAIVPOXBKFXVERMMHUVXINKHNYRXGVLLSPVQDOQNGMPEMSTXRAXFTHPYDNGYDLCRXGMGAYPXPPDLFNXATNFXEHNQRCLIHLENGTMYXYDMHYDVQLZOHDQYIFNOXVHWRSXGOVQHIWFYTHPPHAPNTZTQRVLDHNGHNHVYDATHDWHZNVQTMHXHWSXHNOXBKMKXEXEZNKNEVFTLZWMATPYFCFUHRGMHNTHPMIHXEXEMHTSZXMYTHTASXHNMCUKVLOXPMNTHGYDKFZNCUTHAYMVTBYDWMATPQWHGZHQTMHXHCAINFOHRDKOTMYXYDMHYDQCFNPHVHOXMAQYHRYLNXATTHACNKLZWMATURDRPNVPEBLVXQLZWMATLSPRHNSXTDPMMCVUFUHTOKXLXOTATMFNTMDZVHOXGMHNUVRQGLGXUMUXGLFOFCPVHNYRLVUZRCNKHVSXTDLZWMATNFXEHNQRCLIHLENGYDGXSGVUFUGAUPHRATOHNGMYZBNXATYDUVTATMLZWMATNFXEHNDVHNVPLZWMATTMEXSFMPHRPLDIDHUXHNEMXHNGHNQRCLIHLFCLPRDHIHMSHDAEUVCLAHNGYDLZAVRUDRYLNXATTMQOHPIHIKNZTHCAFOPMFBLZWMATMYVPDQSXLSMSHXDHNGYDTMHYUVRLRVOHVNNZCRPHCICAPQHLMCHCOHRDAKIHCANZDHNGXEXEZNGAUPHPZGDHQVVPPHHGEMZUCHOXKNVXPARVHGZXCATFAKVPHNHIOXBKMKWHRQHPXZXFHONGGNWFNHYDPLSXOHLZWMATTMEXMCUKVLRYHGNVHTDZMHNTBGXGDHNGMPMCNFGXVHCDRXRQGNRDLHLZWMATLSPRNTHONGEMOTGNHNMVGSRFNXATNTIROTPYHVATHDUFAYCAMPGAYIEMRDPYLSPVOXHATMZBLVUZTMOXHNVPPWLEUKRDUXMHNGYDLZAVRUDRYLNXATKWHTOUVNNZFNHNDQNFUWHPYDQCRDMCMCHCTLMVLZWMATHNMVPUOTXUFNTAMSAYPUMTOHHNUVGRHRVQHXHROHATHDIHRQDRHNTHXUFNSFMPHRVMITVLHTMHEVFVNZOXBKHCOHYZTMXGYLLVUCRDMZHRAIYRNXATTMHLAKVPGXSGMVTLHAYRCLQRXFCDYDEVLFYDQXGVMAQZDNXFHDLCOHNFXEXUNZHDPRAKNTKACLIHAPDNXKNHGNLSXGIHMVHNUVFAIWZQATOMVHLENGTMZBLVXZKUHVVQLZXFQODIHPNTBHSXCLDVOAQZKMLURQYXMPQNPACMOXGMHNHVYDDNGIEVOLOXMZTHWHRQHPTMHLPHCAAGYDLZAVYDMCMHDHOXGMHNDVHNVPPWLEZFNXATVQVROTYDMCVZNGNTAIDHYZIHLZWMATFCIHGNHRGMHNYRVLMHXLZLNXATVNMVFNDNAPPMIHHNVPYIFNLTPVTHRAZLGSAKYDATGZMKIHOXPMRQAGNFHLGMHNUVLZWMATLSPRKNDNIYEXMCVZNGUFAYLTXLXOZFCLYRLVMCAKVPCACGMKHNDVGOFLZXLZUAVLPHHXYRNXATNFEWOTLZWMATURDZXSOAQYLHPCRMZVMVDZIFYDLHDZIUSXGOPYFNDXXOTATMFNTMDZAKYDWANXATTMHLPYGMPHAITMHNTMVNIHSLHNHIOXBKLCMVNFPVHNDVOAHBEMOTZUVLHNNTIROTMVHNUVXZLAYLNXATZNATGMPHCIYDHNVPNZVRNFFLZXVLTATMOXHTAKVPHNYRLVUZNTODNZVRHNSXTDGMHNUVNOVPLZWMATTMOLHDRWHDEXXZXFHGCENTLEGNPDKNNXYPLCMVOQNGYZDXXOFXFBDZWFTAHRGXOTTMEGXFRDHXDVLUAKYDNKFTYRNXATTMQLLVWUNTBHSXNFEWTAUFPVHNDPPVTHNSUXGLGDRIHIYPLCMVNFOUVNNZFNIYPDGMGNHNDIHIVPCAYLMPQHNGMEVGQVZLNXATNFXEOXLVHNQDCLVHNKCDLZWMATVUZADQSXVQHITMMXSXNKNDRNHPYDXHNGNDLZWMATQDVUTATMMXSXZFNXATPVKMAVDHHNQVFCPVFLZXOXPMPMOUUFAYTMMSLZUAVLHTGCQRDIDRMVTBSGZNXZVHUVCRXLXGOXBMDRAFNXATNFXEHNDPRPAFNXATRDKMOKXONGTMQOYDNTOHDHHNYPFNPQGMGNHNQVFCPVFLZXOXGMHNVPYIVPHVSLHVRYNFHTGLCGHBYDLVLHVUHDZNCBNXATTMHGYDACOHMCVFSXTDTMQXMHXRRDOL";

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
    std::cout.precision(2);
    simulated_annealing();
    return 0;
}

std::string simulated_annealing(){
    float new_score, saved_score, best_score = -10000000000.0;
    float dF, prob, T = TEMP;
    std::string new_key, best_key, saved_key = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    saved_score = fitness(saved_key);
    for (int step = 1; step < MAX_STEP + 1; step++) {
        // randomly modify key
        new_key = rand_modify(saved_key);
        new_score = fitness(new_key);

        dF = new_score - saved_score;
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
        if (saved_score > best_score){
            best_score = saved_score;
            best_key = saved_key;
        }
        if (step % COOL_STEP == 0) T *= COOL_RATIO;
        if (step % RESET_STEP == 0) T = TEMP;
        // if (step % LOG_STEP == 0) std::cout << std::fixed << step / (float)MAX_STEP * 100 << "%, best_score:" << best_score << ", T:" << T  << ", saved_score:" << saved_score << ", plaintext:" << decode(saved_key) << std::endl;
        if (step % LOG_STEP == 0) std::cout << std::fixed << step / (float)MAX_STEP * 100 << "%, best_score:" << best_score << ", T:" << T  << ", saved_score:" << saved_score << std::endl;
    }
    std::string plain = decode(best_key);
    std::cout << "\nplaintext:" << plain << std::endl;
    return plain;
}

std::string rand_modify(std::string key){
    size_t r = rand() % 50;
    std::string new_key = key;
    switch (r)
    {
    case 0:
        swap_cols(new_key);
        break;
    case 1:
        swap_rows(new_key);
        break;
    case 2:
        rev_col(new_key);
        break;
    case 3:
        rev_row(new_key);
        break;
    default:
        swap_letters(new_key);
        break;
    }
    return new_key;
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

float fitness(std::string key){
    std::string plain = decode(key);
    float score = 0;
    for (int i = 0; i < plain.length() - 3; i++) {
        score += quad[plain.substr(i, 4)];
    }
    score /= cipher.length();
    return score;
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