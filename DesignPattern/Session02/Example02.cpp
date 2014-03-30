// Problem scenario: an order processing system.
// A number of actions are required, such as computing taxes or using a particular
// currency, that are typically different between countries, but can be the same.
// Also, each action may have variations that depend upon run time parameters.
// The specs grew to include 3 countries and 3 actions with 1 to 3 implementations.
// Show a redesign using the strategy pattern that will require only a linear amount
// of code to be added or changed, such changes being well localized, and handling
// any addition of country, action, implementation, or run time dependency.
// Below is the existing code (a bit stylized and abstracted for academic purposes).

enum CountryCode {
        USA,
        Canada,
        Germany
};

const char* CountryName[] = {
        "USA",
        "Canada",
        "Germany"
};

bool electionYear = true;

// In some file.
void taxes(CountryCode country, bool electionYear=true) {
        switch(country) {
        case USA:               cout << "Compute complex taxes for " << CountryName[country] << "." << endl;    break;
        case Canada:
                if(electionYear) {
                        cout << "Compute election taxes for ";
                } else {
                        cout << "Compute complex taxes for ";
                }
                cout << CountryName[country] << "." << endl;    break;
        case Germany:   cout << "Compute complex taxes for " << CountryName[country] << "." << endl;    break;
        }
}

// In some other file.
void currency(CountryCode country) {
        switch(country) {
        case USA:               cout << "Use currency in dollars for " << CountryName[country] << "." << endl;  break;
        case Canada:    cout << "Use currency in dollars for " << CountryName[country] << "." << endl;  break;
        case Germany:   cout << "Use currency in euros for " << CountryName[country] << "." << endl;    break;
        }
}

// In yet another file...
void dateFormat(CountryCode country) {
        switch(country) {
        case USA:               cout << "Use MMDDYY date format for " << CountryName[country] << "." << endl;   break;
        case Canada:    cout << "Use MMDDCCYY date format for " << CountryName[country] << "." << endl; break;
        case Germany:   cout << "Use CCYYMMDD date format for " << CountryName[country] << "." << endl; break;
        }
}

void demo(bool electionYear=true) {
        cout << "*** multipleCaseStatements demo ***" << endl;

        CountryCode countries[] = { USA, Canada, Germany };
        for(size_t i=0; i<sizeof(countries)/sizeof(CountryCode); i++) {
                taxes(countries[i], electionYear);
                currency(countries[i]);
                dateFormat(countries[i]);
        }
}

// Spec change 1: add another country (India).
// Spec change 2: add another implementation (simple taxes).
// Spec change 3: add another action (shipping).

}
