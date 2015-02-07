/*
 * strategy.h
 *
 * Desc: Define a family of interchangeable algorithms which can vary independently from the clients.
 *
 * Category: Behavioral
 *
 *  Created on: Mar 29, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Strategy
 *  	http://www.dofactory.com/net/strategy-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter9
 *  	http://sourcemaking.com/design_patterns/strategy
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

/* Consider a sales order processing system.
 * It must compute tax amounts that depend on country.
 * The legacy code below is typical of how such a system may initially evolve.
 * However, it won't scale well.
 * The multiple switch statements are an Anti-Pattern.
 * Consider what is required to maintain these switch statements under new specs.
 * New specs:
 *   Add new tax rules for Canada
 *     Different rate for election years 6.9%
 *   Add new currency symbol for Quebec orders '#'
 *   Add Germany
 *     new tax rules 10.5%
 *     new currency symbol 'e'
 *   Add date format
 *     USA & Canada - MMDDYY
 *     Germany - DDMMCCYY
 * This is shown in the code section under the strategy_problem namespace.
 * Refactor the legacy code using the strategy pattern.
 *   1) Implement the new specs
 *   2) Avoid code duplication
 *   3) Avoid need for exceptions
 *   4) Avoid having to change existing code as much as possible
 *   	a) New tax specs
 *   	b) New currency symbol
 *   	c) New country
 *   5) Adding the date format spec will require changing existing code even with DP
 *   6) Make sure you get the same results as from the problem namespace code
 */

/* PS  I'm not entirely happy with this example,
 * it is simultaneously too complicated and too simplistic,
 * but it follows the development of chapter 9 in DPE.
 * As formulated, the strategy pattern is needed only for the tax calculation.
 * ... it's an academic exercise... :(
 */
#include <string>
#include <iostream>
#define BUFFER_MAX_SIZE 200
namespace strategy_legacy {

    enum CountryCode {
        USA,
        Canada,
    };

    const char* CountryName[] = {
        "USA",
        "Canada",
    };

    // In tax file...
    double taxAmount(int num, double price, CountryCode cc = USA) {
        double tax = 0;

        switch (cc) {
        case USA:
            tax = 0.075*num*price;
            break;
        case Canada:
            tax = 0.065*num*price;
            break;
        default:
            throw "OOPS";
            break;
        }

        return tax;
    }

    // In currency file...
    char currencySymbol(CountryCode cc = USA) {
        char symbol = ' ';

        switch (cc) {
        case USA:
            symbol = '$';
            break;
        case Canada:
            symbol = '$';
            break;
        default:
            throw "OOPS";
            break;
        }

        return symbol;
    }

    class SalesOrder {
    public:
        int	 number;
        double	price;
        CountryCode countryCode;
    public:
        void process() {
            char str[BUFFER_MAX_SIZE];
            char   sym = currencySymbol(countryCode);
            double tax = taxAmount(number, price, countryCode);
            sprintf_s(str, BUFFER_MAX_SIZE, "%c%.2f for %s order.", sym, tax, CountryName[countryCode]);
            std::cout << str << "\n";
        }
    };

    void demo() {
        SalesOrder orders[] = {
            { 5, 10.00, USA },
            { 1, 20.00, Canada },
        };

        for (size_t i = 0; i < sizeof(orders) / sizeof(SalesOrder); i++) {
            std::cout << "  " << i + 1 << ") ";
            orders[i].process();
        }

        std::cout << std::endl;
    }

}

namespace strategy_problem {

    enum CountryCode {
        USA,
        Canada,
        Germany,
        // Country seam point.
    };

    const char* CountryName[] = {
        "USA",
        "Canada",
        "Germany",
        // Country seam point.
    };

    // Run time requirements.
    bool electionYear() { return true; }
    bool Quebec() { return true; }

    // In tax file...
    double taxAmount(int num, double price, CountryCode cc = USA) {
        double tax = 0;

        switch (cc) {
        case USA:
            tax = 0.075*num*price;
            break;
        case Canada:
            if (electionYear())
                tax = 0.069*num*price;
            else
                tax = 0.065*num*price;
            break;
        case Germany:
            tax = 0.105*num*price;
            break;
            // Country seam point.
        default:
            throw "OOPS";
            break;
        }

        return tax;
    }

    // In currency file...
    char currencySymbol(CountryCode cc = USA) {
        char symbol = ' ';

        switch (cc) {
        case USA:
            symbol = '$';
            break;
        case Canada:
            if (Quebec())
                symbol = '#';
            else
                symbol = '$';
            break;
        case Germany:
            symbol = 'e';
            break;
            // Country seam point.
        default:
            throw "OOPS";
            break;
        }

        return symbol;
    }

    // In new date format file...
    std::string dateFormat(CountryCode cc = USA) {
        std::string fmt = "";

        switch (cc) {
        case USA:
        case Canada:
            fmt = "MMDDYY";
            break;
        case Germany:
            fmt = "DDMMCCYY";
            break;
            // Country seam point (this makes 5).
        default:
            throw "OOPS";
            break;
        }

        return fmt;
    }

    class SalesOrder {
    public:
        int	 number;
        double	price;
        CountryCode countryCode;
    public:
        void process() {
            char str[BUFFER_MAX_SIZE];
            char   sym = currencySymbol(countryCode);
            double tax = taxAmount(number, price, countryCode);
            std::string fmt = dateFormat(countryCode);
            sprintf_s(str, BUFFER_MAX_SIZE, "%c%.2f for %s order on %s.",
                sym, tax, CountryName[countryCode], fmt.c_str());
            std::cout << str << "\n";
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


namespace strategy_strategy {
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
#endif /* STRATEGY_H_ */

