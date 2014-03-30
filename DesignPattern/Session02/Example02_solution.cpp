// Actions (with implementations).
class Taxes {public: virtual void use() {cout << "  Taxes: ";} virtual ~Taxes() {}};
class Complex : public Taxes {public: void use() { Taxes::use(); cout << "complex." << endl;}};
class Election : public Taxes {public: void use() { Taxes::use(); cout << "election." << endl;}};
// Seam point: add another tax.
class Simple : public Taxes {public: void use() { Taxes::use(); cout << "simple." << endl;}};

class Currency {public: virtual void use() {cout << "  Currency: ";} virtual ~Currency() {}};
class Dollars : public Currency {public: void use() { Currency::use(); cout << "dollars." << endl;}};
class Euros   : public Currency {public: void use() { Currency::use(); cout << "euros." << endl;}};
// Seam point: add another Currency.

class DateFormat {public: virtual void use() {cout << "  DateFormat: ";} virtual ~DateFormat() {}};
class MMDDYY  : public DateFormat {public: void use() { DateFormat::use(); cout << "MMDDYY." << endl;}};
class MMDDCCYY : public DateFormat {public: void use() { DateFormat::use(); cout << "MMDDCCYY." << endl;}};
class CCYYMMDD  : public DateFormat {public: void use() { DateFormat::use(); cout << "CCYYMMDD." << endl;}};
// Seam point: add another DateFormat.

// Seam point: add another action (with at least one implementation).
class Shipping {public: virtual void use() {cout << "  Shipping: default" << endl;} virtual ~Shipping() {}};
class UPS : public Shipping {public: void use() { cout << "  Shipping: UPS." << endl;}};

// Countries, base class with derived classes.
class Country {
public:
        const char* name;
        Taxes*          taxes;          // Actions.
        Currency*       currency;
        DateFormat*     dateFormat;
        // Seam point: add another action.
        Shipping*       shipping;
public:
        Country(const char* name, Taxes* taxes, Currency* currency, DateFormat* dateFormat, /*Seam*/ Shipping* shipping=new Shipping)
        : name(name), taxes(taxes), currency(currency), dateFormat(dateFormat), /*Seam*/ shipping(shipping) {}
        void changeTaxes(Taxes* newTaxes) { taxes = newTaxes; }
        void changeCurrency(Currency* newCurrency) { currency = newCurrency; }
        void changeDateFormat(DateFormat* newDateFormat) { dateFormat = newDateFormat; }
        // Seam point: add another action.
        void changeShipping(Shipping* newShipping) { shipping = newShipping; }
};

class USA : public Country { public:
        USA() : Country("USA", new Complex, new Dollars, new MMDDYY) {}
};
class Canada : public Country { public:
        Canada() : Country("Canada", new Complex, new Dollars, new MMDDCCYY) {}
};
class Germany : public Country { public:
        Germany() : Country("Germany", new Complex, new Euros, new CCYYMMDD) {}
};
// Seam point: add another Country.
class India : public Country { public:
        India() : Country("India", new Simple, new Euros, new CCYYMMDD, /*Seam*/ new UPS) {}
};

void demo(bool electionYear=true) {
        cout << "*** strategy3 demo ***" << endl;

        Country* countries[] = { new USA, new Canada, new Germany, /*Seam*/ new India }; // Seam point: add another country.
        if(electionYear) countries[1]->changeTaxes(new Election);       //Special case.

        for(size_t i=0; i<sizeof(countries)/sizeof(Country*); i++) {
                Country* country = countries[i];
                cout << country->name << ": " << endl;
                country->taxes->use();
                country->currency->use();
                country->dateFormat->use();
                // Seam point: add another action.
                country->shipping->use();
        }
}
