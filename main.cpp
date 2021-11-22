//头文件
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <set>
using namespace std;
const int MAXNUM = 65535;
const int NUM = 100;
vector<string> Reserve(NUM);
vector<string> Operator(NUM*3);
vector<string> Boundary(NUM*2);
bool flag[NUM*3];
set<string> sets = {"int","char","string","float","short","double","void"};
set<double> doubleset;
set<string> usersets;
void InitReserve() {//构造保留字表的函数
    Reserve[1] = "main";
    Reserve[2] = "int";
    Reserve[3] = "if";
    Reserve[4] = "else";
    Reserve[5] = "while";
    Reserve[6] = "for";
    Reserve[7] = "read";
    Reserve[8] = "write";
    Reserve[9] = "bool";
    Reserve[10] = "break";
    Reserve[11] = "case";
    Reserve[12] = "catch";
    Reserve[13] = "char";
    Reserve[14] = "class";
    Reserve[15] = "const";
    Reserve[16] = "continue";
    Reserve[17] = "default";
    Reserve[18] = "delete";
    Reserve[19] = "do";
    Reserve[20] = "double";
    Reserve[21] = "enum";
    Reserve[22] = "false";
    Reserve[23] = "true";
    Reserve[24] = "float";
    Reserve[25] = "friend";
    Reserve[26] = "goto";
    Reserve[27] = "inline";
    Reserve[28] = "long";
    Reserve[29] = "new";
    Reserve[30] = "private";
    Reserve[31] = "protected";
    Reserve[32] = "public";
    Reserve[33] = "return";
    Reserve[34] = "short";
    Reserve[35] = "signed";
    Reserve[36] = "sizeof";
    Reserve[37] = "static";
    Reserve[38] = "struct";
    Reserve[39] = "switch";
    Reserve[40] = "this";
    Reserve[41] = "try";
    Reserve[42] = "typedef";
    Reserve[43] = "unsigned";
    Reserve[44] = "using";
    Reserve[45] = "virtual";
    Reserve[46] = "void";
    Reserve[47] = "include";
    Reserve[48] = "iostream";
    Reserve[49] = "namespace";
    Reserve[50] = "std";
    Reserve[51] = "string";
    Reserve[52] = "auto";
}
void InitOperator() {//初始化运算符表
    Operator[210] = "+";
    Operator[211] = "-";
    Operator[212] = "*";
    Operator[213] = "/";
    Operator[214] = "<";
    Operator[215] = "<=";
    Operator[216] = ">";
    Operator[217] = ">=";
    Operator[218] = "!=";
    Operator[219] = "==";
    Operator[220] = "=";
    Operator[221] = "?";
    Operator[222] = "&";
    Operator[223] = "|";
    Operator[224] = "^";
    Operator[225] = "||";
    Operator[226] = "&&";
    Operator[227] = "<<";
    Operator[228] = ">>";

}
void InitBoundary() {//界符表初始化
    Boundary[121] = "(";
    Boundary[122] = ")";
    Boundary[123] = ",";
    Boundary[124] = ";";
    Boundary[125] = "{";
    Boundary[126] = "}";
    Boundary[127] = "#";
    Boundary[128] = "\"";
    Boundary[129] = "[";
    Boundary[130] = "]";
}

string FiLeRead(){
    string s;
    char c;
    ifstream in("input.txt");
    if (! in.is_open()) {
        cout << "Error opening file";
        exit (1);
    }
    while ((c = in.get()) != EOF ) s += c;
    return s;
}

void FileOutput(string reserve){
    ofstream out;
    out.open("output.txt",ios::app);
    if(!out){
        cout << "open file failed" << endl;
        return;
    }
    out << reserve;
    out.close();
}

void FileOutputInteger(string reserve){
    ofstream out;
    out.open("unInt.txt",ios::app);
    if(!out){
        cout << "open file failed" << endl;
        return;
    }
    out << reserve;
    out.close();
}

void FileOutputDouble(string reserve){
    ofstream out;
    out.open("unFloat.txt",ios::app);
    if(!out){
        cout << "open file failed" << endl;
        return;
    }
    out << reserve;
    out.close();
}

void FileOutputUser(string reserve){
    ofstream out;
    out.open("idList.txt",ios::app);
    if(!out){
        cout << "open file failed" << endl;
        return;
    }
    out << reserve;
    out.close();
}

void ShowTable() {
    cout << "========================" << "保留字" << "========================" << endl;
    cout << "  保留字符\t类别编码\t字段类型\t字段大小" << endl;
    for (int i = 1; i <= 50; i++) {
        cout <<setw(9)<< Reserve[i] <<setw(10)<< i << endl;
    }
    cout << "\n=======" << "界符" << "=======" << endl;
    cout << "界符\t类别编码" << endl;
    for (int i = 121; i <= 130; i++) {
        cout <<" "<< Boundary[i] << "\t " << i << endl;
    }
    cout << "\n===========" << "运算符" << "============" << endl;
    cout << "运算符\t\t类别编码" << endl;
    for (int i = 210; i <= 226; i++) {
        cout <<"  "<< Operator[i] << "\t\t  " << i << endl;
    }
}

int isReserve(string temp){
    for(int i = 1;i <= 52;i++){
        if(Reserve[i] == temp){
            return i;
        }
    }
    return -1;
}



vector<string> split (const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    while(i != s.size())
    {
        while(i!=s.size() && isspace(s[i]))  //此处是跳过空白字符
            i++;
        string_size j = i;
        while(j!=s.size() && !isspace(s[j])) //此处就是从非空白符开始到遇到
            j++;                            //空白符结束，即[ i, j )之间的单词
        //如果是非空字符就加入到vector中去
        if(i!=j)
        {
            ret.push_back(s.substr(i, j-i));
            i=j;
        }
    }
    return ret;
}


void Analyse(string code) {
    int i = 0;
    string temp = "";
    if(code.find("@") != code.npos) {
        FileOutput("Error:Illegal character:@\n");
    }
    while(i < code.length()){
        if(code[i] == ' ') {i++;continue;}
        if(code[i] == '\n'){i++;continue;}
        if(code[i] == '\t') {i++;continue;}
        if(isalpha(code[i]) && isalpha(code[i+1])){
            temp += code[i];
        }else if(isalpha(code[i]) && !isalpha(code[i+1]) ){
            temp += code[i];
            //cout << temp << endl;
            int res = isReserve(temp);
            if(res >= 1 && res <= 52){
                if(!flag[res]){
                    //temp = "(" + to_string(res) +","+ Reserve[res] +")\n";
                    temp = "(Reserve,"+ Reserve[res] +")\n";
                    FileOutput(temp);
                    flag[res] = true;
                }

            }
            temp = "";
        }
        i++;
    }

    //识别运算符
//    reserve = "运算符识别如下：\n";
//    FileOutput(reserve);
    i = 0;
    while(i < code.length()){
        if(code[i] == ' ') {i++;continue;}
        if(code[i] == '\n'){i++;continue;}
        if(code[i] == '\t') {i++;continue;}
        string s(&code[i],1);
        string s2(&code[i+1],1);
        if(s == Operator[210] && !flag[210]) FileOutput("(Operator,"+ Operator[210] +")\n"),flag[210] = true;
        else if(s == Operator[211] && !flag[211]) FileOutput("(Operator,"+ Operator[211] +")\n"),flag[211] = true;
        else if(s == Operator[212] && !flag[212]) FileOutput("(Operator,"+ Operator[212] +")\n"),flag[212] = true;
        else if(s == Operator[213] && !flag[213]) FileOutput("(Operator,"+ Operator[213] +")\n"),flag[213] = true;
        else if(s == Operator[214] && s2 != "=" && s2 != "<" && !flag[214]) FileOutput("(Operator,"+ Operator[214] +")\n"),flag[214] = true;
        else if(s == Operator[214] && s2 == "=" && !flag[215]) FileOutput("(Operator,"+ Operator[215] +")\n"),flag[215] = true;
        else if(s == Operator[216] && s2 != "=" && s2 != ">" && !flag[216]) FileOutput("(Operator,"+ Operator[216]+")\n"),flag[216] = true;
        else if(s == Operator[216] && s2 == "=" && !flag[217]) FileOutput("(Operator,"+ Operator[217] +")\n"),flag[217] = true;
        else if(s + s2 == "!=" && !flag[218]) FileOutput("(Operator,"+ Operator[218] +")\n"),flag[218] = true;
        else if(s + s2 == "==" && !flag[219] ) FileOutput("(Operator,"+ Operator[219] +")\n"),flag[219] = true;
        else if(s == Operator[221] && !flag[221]) FileOutput("(Operator,"+ Operator[221] +")\n"),flag[221] = true;
        else if(s == Operator[222] && s2 != "&" && !flag[222]) FileOutput("(Operator,"+ Operator[222] +")\n"),flag[222] = true;
        else if(s == Operator[223] && s2 != "|" && !flag[223]) FileOutput("(Operator,"+ Operator[223] +")\n"),flag[223] = true;
        else if(s == Operator[224] && !flag[224]) FileOutput("(Operator,"+ Operator[224] +")\n"),flag[224] = true;
        else if(s == Operator[220] && !flag[220]) FileOutput("(Operator,"+ Operator[220] +")\n"),flag[220] = true;
        else if(s == "|" &&  s2 == "|" && !flag[225]) FileOutput("(Operator,"+ Operator[225] +")\n"),flag[225] = true;
        else if(s == "&" && s2 == "&" && !flag[226]) FileOutput("(Operator,"+ Operator[226] +")\n"),flag[226] = true;
        else if(s == "<" && s2 == "<" && !flag[227]) FileOutput("(Operator,"+ Operator[227] +")\n"),flag[227] = true;
        else if(s == ">" && s2 == ">" && !flag[228]) FileOutput("(Operator,"+ Operator[228] +")\n"),flag[228] = true;
        i++;
    }
    //识别分隔符
//    reserve = "分隔符识别如下：\n";
//    FileOutput(reserve);
    i = 0;
    while(i < code.length()){
        if(code[i] == ' ') {i++;continue;}
        if(code[i] == '\n'){i++;continue;}
        if(code[i] == '\t') {i++;continue;}
        switch (code[i]) {
            case '(':if(!flag[121]) FileOutput("(separation,"+ Boundary[121] +")\n"); flag[121] = true;break;
            case ')':if(!flag[122]) FileOutput("(separation,"+ Boundary[122] +")\n"); flag[122] = true;break;
            case ',':if(!flag[123]) FileOutput("(separation,"+ Boundary[123] +")\n"); flag[123] = true;break;
            case ';':if(!flag[124]) FileOutput("(separation,"+ Boundary[124] +")\n"); flag[124] = true;break;
            case '{':if(!flag[125]) FileOutput("(separation,"+ Boundary[125] +")\n"); flag[125] = true;break;
            case '}':if(!flag[126]) FileOutput("(separation,"+ Boundary[126] +")\n"); flag[126] = true;break;
            case '#':if(!flag[127]) FileOutput("(separation,"+ Boundary[127] +")\n"); flag[127] = true;break;
            case '\"':if(!flag[128]) FileOutput("(separation,"+ Boundary[128] +")\n"); flag[128] = true;break;
            case '[':if(!flag[129]) FileOutput("(separation,"+ Boundary[129] +")\n"); flag[129] = true;break;
            case ']':if(!flag[130]) FileOutput("(separation,"+ Boundary[130] +")\n"); flag[130] = true;break;
        }
        i++;
    }

    //识别无符号数
//    reserve = "浮点数识别如下：\n";
//    FileOutput(reserve);
    FileOutputDouble("无符号浮点数\t\t\t类型\t\t存储位置\n");
    i = 0;
    temp = "";
    while(i < code.length()){
        if(code[i] == ' ') {i++;continue;}
        if(code[i] == '\n'){i++;continue;}
        if(code[i] == '\t') {i++;continue;}
        if((isdigit(code[i]) || code[i] == '.')&& (isdigit(code[i+1]) || code[i+1] == '.')){
            temp += code[i];
        }else if(isdigit(code[i])&& !isdigit(code[i+1]) ){
            temp += code[i];
            if(doubleset.find(atof(temp.c_str())) == doubleset.end() && temp.find('.') != temp.npos){
                temp = to_string(atof(temp.c_str())*1.000000).substr(0,temp.find(".")+4);
                FileOutput("(double,"+ temp +")\n");
                FileOutputDouble(temp+"\n");
                doubleset.insert(atof(temp.c_str()));
                temp = "";
            }else temp = "";

        }
        i++;
    }

    //识别无符号数
//    reserve = "整数识别如下：\n";
//    FileOutput(reserve);
    FileOutputInteger("无符号整数\t\t\t类型\t\t存储位置\n");
    i = 0;
    temp = "";
    while(i < code.length()){
        if(code[i] == ' ') {i++;continue;}
        if(code[i] == '\n'){i++;continue;}
        if(code[i] == '\t') {i++;continue;}
        if((isdigit(code[i]) || code[i] == '.')&& (isdigit(code[i+1]) || code[i+1] == '.')){
            temp += code[i];
        }else if(isdigit(code[i])&& !isdigit(code[i+1]) ){
            temp += code[i];
            if(doubleset.find(atof(temp.c_str())) == doubleset.end() && temp.find('.') == temp.npos){
                FileOutput("(integer,"+ temp +")\n");
                FileOutputInteger(temp+"\n");
                doubleset.insert(atof(temp.c_str()));
                temp = "";
            }else temp = "";

        }
        i++;
    }


    //识别用户保留字段
//    reserve = "用户保留字段如下：\n";
    FileOutputUser("标识符名\t\t\t类型\t\t存储位置\n");
    vector<string> userkeywords(MAXNUM);
    userkeywords = split(code);
    for(vector<string>::iterator it = userkeywords.begin();it != userkeywords.end();){
        if(sets.find(*it) != sets.end()){
            ++it;
            if((*it).find('(') != (*it).npos && usersets.count((*it).substr(0,(*it).find('(') )) == 0){
                if((*it).substr(0,(*it).find('(') ) != "main") {
                    FileOutput("(Id,"+(*it).substr(0, (*it).find('(')) + ")\n");
                    FileOutputUser((*it).substr(0, (*it).find('(')) + "\n");
                    usersets.insert((*it).substr(0, (*it).find('(')));
                }
            }
            else if((*it).find('=') != (*it).npos && usersets.count((*it).substr(0,(*it).find('=') )) == 0){
                FileOutput("(Id,"+(*it).substr(0,(*it).find('=') ) + ")\n");
                FileOutputUser((*it).substr(0, (*it).find('(')) + "\n");
                usersets.insert((*it).substr(0,(*it).find('=') ));
            }
            else if((*it).find(';') != (*it).npos && usersets.count((*it).substr(0,(*it).find(';') )) == 0){
                FileOutput("(Id,"+(*it).substr(0,(*it).find(';') ) + ")\n");
                FileOutputUser((*it).substr(0, (*it).find('(')) + "\n");
                usersets.insert((*it).substr(0,(*it).find(';') ));
            }else if(usersets.count(*it) == 0){
                FileOutput("(Id,"+(*it) + ")\n");
                FileOutputUser((*it).substr(0, (*it).find('(')) + "\n");
                usersets.insert((*it) + '\n');
            }
        }
        ++it;
    }
}

int main(){
    string code;
    code = FiLeRead();
    InitOperator();
    InitReserve();
    InitBoundary();
    ShowTable();
    Analyse(code);
}


