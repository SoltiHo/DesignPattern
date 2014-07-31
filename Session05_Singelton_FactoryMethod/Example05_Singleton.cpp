/* Consider the requirement that there be only one instance of a class.
* This could be because it implements an interface to a limited resource.
* For this exercise the "resource" is a global variable (it's just an exercise).
* Replace the OnlyOneOf class, which doesn't enforce the Singleton pattern,
* with a class that does. What do you have to implement to prevent a
* user from instantiating more than one instance of a Singleton class?
*/

namespace too_many {

    static int resource = 1;

    class OnlyOneOf {
    public:
        OnlyOneOf() {
            cout << "  Construction happens on every call to ctor.\n";
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
        cout << "<< Singleton problem >>\n";

        OnlyOneOf foo;
        OnlyOneOf bar;

        foo.accessFiniteResource(1);
        bar.accessFiniteResource(2);

        if (&foo == &bar)     cout << "  foo and bar are same object, expect 2 & 2.\n";
        else                       cout << "  foo and bar are different objects, expect 1 & 2.\n";

        cout << "    foo = " << foo.accessFiniteResource() << "\n";
        cout << "    bar = " << bar.accessFiniteResource() << "\n";

        cout << endl;
    }

}
