#include"iostream"
int main(){
    int ia[5][6]={0};
    for(auto &row:ia){
        for(auto num:row){
            std::cout<<num<<std::endl;
        }
    }
}
