// вынести константы 


#include <iostream>
#include <vector>

using namespace std;

struct Realty {
    double area = 0.0; // площадь
    int numberOfBedrooms = 0; // количество спальных комнат
    int numberOfBathrooms = 0; // количество санузлов
    int distanceToSubway = 0; // расстояние до метро
    bool commercialProperty = false; // комерческое или жилое 
    double price = 0.0; // цена
};

void properties(Realty realty) { // функция вывода данных
    cout << endl;
    cout << "area = " << realty.area << endl;
    cout << "numberOfBedrooms = " << realty.numberOfBedrooms << endl;
    cout << "numberOfBathrooms = " << realty.numberOfBathrooms << endl;
    cout << "distanceToSubway = " << realty.distanceToSubway << endl;
    cout << "commercialProperty = " << realty.commercialProperty << endl;
    cout << "price = " << realty.price << endl;
}

bool requestProperties(Realty &realty, bool withPrice) { // функция запроса данных
    
    const int maxBedrooms = 5, minBedrooms = 0;
    const int maxBathrooms = 5, minBathrooms = 0;
    const int minDistanceToSubway = 0;
    const int minPrice = 30000;
    const int endDataInputNumber = 0;
    
    cout << "Enter the area: ";
    cin >> realty.area;
    if(realty.area == endDataInputNumber) {
        return false;
    }
        
    while(true) {
        cout << "Enter the number of bedrooms: ";
        cin >> realty.numberOfBedrooms;
        if(realty.numberOfBedrooms > maxBedrooms) {
            cout << "Why do you need more than 5 bedrooms?" << endl; 
            continue;
        }
        if(realty.numberOfBedrooms < minBedrooms) {
            cout << "?" << endl; 
            continue;
        }
        
        break;
    }
    
    while(true) {
        cout << "Enter the number of bathrooms: ";
        cin >> realty.numberOfBathrooms;
        if(realty.numberOfBathrooms > 5) {
            cout << "Why do you need more than 5 bathrooms?" << endl; 
            continue;
        }
        if(realty.numberOfBathrooms < 0) {
            cout << "?" << endl; 
            continue;
        }

        break;
    }
    
    while(true) {
        cout << "Enter the max distance to subway (in meters): ";
        cin >> realty.distanceToSubway;
        if(realty.distanceToSubway < minDistanceToSubway) {
            cout << "What ?" << endl; 
            continue;
        }

        break;
    }
        
    while(true) {    
        cout << "Enter the type of housing (1 - commercial, 0 - residential): ";
        int a;
        cin >> a;
        if(a != 0 && a != 1) {
            cout << "I gave you two choices 1 or 0, but you chose something else..." << endl; 
            continue;
        }

        realty.commercialProperty = a == 1; // если 1 == 1, то true, а если 0 == 1, то false    
        break;
    }
    
    while(withPrice) {
        cout << "Enter the max price in $: ";
        cin >> realty.price;
        if(realty.price < minPrice) {
            cout << "We don't have realty than price less than 30000$" << endl; 
            continue;
        }
        break;
    }
    
    return true;
}

double predict(Realty target, vector<Realty> features) {
    double price = 0.0; // цена нашего жилья
    double averagePrice = 0.0; // среднее арифметическое 
//    double maxPrice = 0.0; 
    double sumPrice = 0.0; 

    int n = 0;
    for(int i = 0; i < features.size(); i++) { // цикл перебора елементов вектора
        Realty realty = features[i];
        
        if (target.commercialProperty != realty.commercialProperty) { // поиск жилья с одинаковым типом (комерция или нет)
            continue; // возврат к началу цикла 
        }
        
        n++;
        sumPrice += realty.price; // суммирование всех цен вектора 
//        if (maxPrice < realty.price) { 
//            maxPrice = realty.price; // нахождение максмальной цены вектора
//        }
        
    }
    
    averagePrice = n == 0 ? 0 : sumPrice / n; // форумла среднего арифметического // c ? x : y // Если c — ненулевое значение (true), то вычисляется x, в противном случае — y
    
    price = averagePrice * 1.05; // формула подсчёта цены (среднее арифметическое цен вектора умноженое на 105%)
    //price = maxPrice * 1.05; // формула подсчёта цены (максимальная цена елемента вектора домноженая на 105%)

    return price;
}

int main() {
    Realty realty;
    Realty target;
    vector<Realty> features;

    bool success = true;
    
    cout << "Now you are entering data, if you want to finish entering, enter the value 0 in the \"area\" field" << endl;
    while (success) {
        
        success = requestProperties(realty, true);
        
        if (success == true) {
            features.push_back(realty);
        }
        else {
            cout << endl << "Was entered realties: " << features.size() << endl;
            cout << "End data input!" << endl << endl;
        }
    }
    
    cout << "Enter target realty properties (if you want to exit the program, enter 0 in the \"area\" field )" << endl;
    
    char x = 'N';
    while (x != 'Y' && x != 'y') {
        requestProperties(target, false);
        
        target.price = predict(target, features);
        
        properties(target);
        
        if (target.price == 0.0) { // в случае если в выборке нету нужного нам типа жилья (commercial or residential)
            cout << "We can't find data about your request" << endl << endl;
        }
        cout << "Do you want exit? Y or N: ";
        cin >> x;
    }

    return 0;
}
