//Kalkulator nentuin jual di INDODAX atau BINANCE

#include <iostream>

using namespace std;

struct market {
  double dogeWallet;
  double dogeMarket;
  double address; //gak penting
};

double net = 0; //Doge Cair
double net_cash_bf = 0; //Uang cair sblm
double net_cash_af = 0; //Uang cair stlh
double biaya_admin = 5; //Biaya admin withdrow DOGE

int keputusan = 0; //cuma buat status mau dijual dimana

void send(double *source, double *destination, double biaya) {
    *destination = *destination + *source-biaya;
    *source = 0;
}

void sell(double *source) {
    net = net + *source;
    *source = 0;
}

double profit(double before, double after){
    return ((after-before)/before)*100;
}

int main()
{
    struct market indodax;
    struct market binance;

    indodax.dogeMarket = 800; //harga market indodax
    binance.dogeMarket = 750; //harga market binance

    indodax.dogeWallet = 1000;    //saldo indodax
    binance.dogeWallet = 1000;    //saldo binance
    
    net_cash_bf = indodax.dogeMarket*indodax.dogeWallet + binance.dogeMarket*binance.dogeWallet + net;
    
    cout.precision(9);
    cout << "Value DOGE before : " << net_cash_bf << "\n";

    cout << "Status " << "DogeIndodax"  << " " << "DogeBinance " << "Cair" << "\n";
    cout << "BeforeSend " << indodax.dogeWallet  << " " << binance.dogeWallet << " " << net << "\n";
    
    if(indodax.dogeMarket < binance.dogeMarket ) {
        send(&indodax.dogeWallet, &binance.dogeWallet, biaya_admin);
        cout << "BeforeSell " << indodax.dogeWallet  << " " << binance.dogeWallet << " " << net << "\n";
        sell(&binance.dogeWallet);
        keputusan = 0;
    }
    else if(indodax.dogeMarket > binance.dogeMarket) {
        send(&binance.dogeWallet, &indodax.dogeWallet, biaya_admin);
        cout << "BeforeSell " << indodax.dogeWallet  << " " << binance.dogeWallet << " " << net << "\n";
        sell(&indodax.dogeWallet);
        keputusan = 1;
    }
    
    cout << "AfterSell " << indodax.dogeWallet  << " " << binance.dogeWallet << " " << net << "\n";
    
    if(indodax.dogeMarket < binance.dogeMarket ) {
        net_cash_af = net * binance.dogeMarket;
    }
    else if(indodax.dogeMarket > binance.dogeMarket) {
         net_cash_af = net * indodax.dogeMarket;
    }
    else {
        net_cash_af = 0;
    }

    cout << "Value DOGE after : " << net_cash_af << "\n";
    cout << "Profit " <<profit(net_cash_bf, net_cash_af) << "%" <<"\n";
    if(keputusan==0) {
        cout << "Jual di BINANCE"<<"\n";
    }
    else if(keputusan==1) {
        cout << "Jual di INDODAX"<<"\n";
    }
    
    return 0;
}
