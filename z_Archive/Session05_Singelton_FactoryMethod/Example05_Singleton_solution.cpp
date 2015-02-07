
namespace singleton {

    static int resource = 1;

    class Singleton {
    private:
        Singleton() {
            cout << "  Construction of singleton only happens once.\n";
        }
        Singleton(const Singleton&);                             // Disallow copy ctor.
        const Singleton& operator=(const Singleton&); // Disallow assignment operator.
        ~Singleton() {}                                                        // Prevent deletion of the single instance.
    public:
        static Singleton& instance() {
            static Singleton* instance = new Singleton;
            return *instance;
        }
    public:
        int accessFiniteResource(int id = -1) {
            if (id < 0)
                return resource;
            else {
                resource = id;
                return resource;
            }
        }
    };

    void demo() {
        cout << "<< Singleton solution >>\n";

        Singleton& foo = Singleton::instance();
        Singleton& bar = Singleton::instance();

        foo.accessFiniteResource(1);
        bar.accessFiniteResource(2);

        if (&foo == &bar)     cout << "  foo and bar are same object, expect 2 & 2.\n";
        else                       cout << "  foo and bar are different objects, expect 1 & 2.\n";

        cout << "    foo = " << foo.accessFiniteResource() << "\n";
        cout << "    bar = " << bar.accessFiniteResource() << "\n";

#ifdef CompilerComplains
        Singleton     sam;
#else
        cout << "  Skipping code snippets prohibited by Singleton DP.\n";
#endif
    }

}