#include "lab1_problem_strategy.h"


namespace strategy_strategy {
    // not so good,  the symbol and the date can be seperate strategies
    enum CountryCode {
        USA,
        Canada,
        Germany,
        // Country seam point.  inevitable?
    };

    const char* CountryName[] = {
        "USA",
        "Canada",
        "Germany",
        // Country seam point.  inevitable?
    };

    class TaxCalculator {
    public:
        CountryCode cc; // country code
        char cs; // currency symbol
        std::string cn; // country name
    public:
        TaxCalculator(CountryCode countryCode, char symbol, std::string name) : cc(countryCode), cs(symbol), cn(name) {};

        virtual void processTax(
            char* buffer,
            const int bufferSize,
            const int number,
            const double price) = 0;
    };

    class USTax : public TaxCalculator {
    public:
        USTax() : TaxCalculator(USA, '$', "USA") {};
        virtual void processTax(char* buffer, const int bufferSize, const int number, const double price) {
            double tax = 0.075*number*price;
            std::string fmt("MMDDYY");
            sprintf_s(buffer, bufferSize, "%c%.2f for %s order on %s.",
                this->cs, tax, this->cn.c_str(), fmt.c_str());
        }
    };

    class CanadaTax : public TaxCalculator {
    public:
        CanadaTax() : TaxCalculator(Canada, '$', "Canada") {
            if (Quebec()){
                this->cs = '#';
            }
        };

        // Run time requirements.
        bool electionYear() { return true; }
        bool Quebec() { return true; }

        virtual void processTax(char* buffer, const int bufferSize, const int number, const double price) {
            double tax = electionYear() ? 0.069*number*price : 0.065*number*price;
            std::string fmt("MMDDYY");
            sprintf_s(buffer, bufferSize, "%c%.2f for %s order on %s.",
                this->cs, tax, this->cn.c_str(), fmt.c_str());
        }
    };

    class GermanyTax : public TaxCalculator {
    public:
        GermanyTax() : TaxCalculator(USA, 'e', "Germany") {};
        virtual void processTax(char* buffer, const int bufferSize, const int number, const double price) {
            double tax = 0.105*number*price;
            std::string fmt("DDMMCCYY");
            sprintf_s(buffer, bufferSize, "%c%.2f for %s order on %s.",
                this->cs, tax, this->cn.c_str(), fmt.c_str());
        }
    };

    class SalesOrder {
    public:
        int	 number;
        double	price;
        CountryCode countryCode;
        TaxCalculator* pTaxCalculator;
    public:
        SalesOrder(int n, double d, CountryCode cc) : number(n), price(d), countryCode(cc), pTaxCalculator(calculatorFactory(cc)){};
        void process() {
            char str[BUFFER_MAX_SIZE];
            this->pTaxCalculator->processTax(str, BUFFER_MAX_SIZE, this->number, this->price);
            std::cout << str << "\n";
        }

        TaxCalculator* calculatorFactory(CountryCode countryCode){
            TaxCalculator* pOutput = NULL;
            switch (countryCode) {
            case USA:
                pOutput = new USTax;
                break;
            case Canada:
                pOutput = new CanadaTax;
                break;
            case Germany:
                pOutput = new GermanyTax;
                break;
                // Country seam point.  inevitable?
            default:
                throw "OOPS";
                break;
            }

            return pOutput;
        }
    };


    void demo() {
        SalesOrder orders[] = {
            { 5, 10.00, USA },
            { 1, 20.00, Canada },
            { 9, 99.99, Germany },
        };

        for (size_t i = 0; i < sizeof(orders) / sizeof(SalesOrder); i++) {
            std::cout << "  " << i + 1 << ") ";
            orders[i].process();
        }

        std::cout << std::endl;
    }
}


void main(){
    std::cout << "------ strategy_legacy demo ------" << std::endl;
    strategy_legacy::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ strategy_problem demo ------" << std::endl;
    strategy_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ strategy_strategy demo ------" << std::endl;
    strategy_strategy::demo();
    std::cout << std::endl << std::endl;

    
}