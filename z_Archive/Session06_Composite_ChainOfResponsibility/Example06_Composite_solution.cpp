namespace composite {

    class Component {                               // No seam points, closed to modification.
    protected:
        string name;
    public:
        Component(string name) : name(name) {}
        virtual ~Component() {}
    public:
        virtual void add(Component* branch) { cout << "OOPS!, can't add to non branches.\n"; };
        virtual void display(int depth) = 0;
    };
    class Composite : public Component {      // No seam points, closed to modification.
        list<Component*> children;
    public:
        Composite(string name) : Component(name) {}
        virtual ~Composite() {}
    public:
        void add(Component* branch) {
            children.push_back(branch);
        }
        void display(int depth) {
            for (int i = 0; i < depth; i++) cout << "-";               // Display this branch.
            cout << " " << name << endl;

            list<Component*>::iterator it = children.begin();     // Display all the child branches.
            for (; it != children.end(); it++) {
                (*it)->display(depth + 2);
            }
        }
    public:
    };
    class Leaf : public Component {
    public:
        virtual ~Leaf() {};
    public:
        Leaf(string name) : Component(name) {}
        void display(int depth) {                                               // Display this leaf.
            for (int i = 0; i < depth; i++) cout << "-";
            cout << " " << name << endl;
        }
    };
    class Bud : public Component {
    public:
        virtual ~Bud() {};
    public:
        Bud(string name) : Component(name) {}
        void display(int depth) {                                               // Display this bud.
            for (int i = 0; i < depth; i++) cout << "-";
            cout << " " << name << endl;
        }
    };
    // Seam point: Add class for fruit.

    void demo() {
        cout << "<< Composite solution >>\n";

        Component* trunk = new Composite("trunk");
        trunk->add(new Leaf("leaf1"));
        trunk->add(new Bud("bud2"));
        trunk->add(new Leaf("leaf3"));

        Component* branch = new Composite("branch4");
        branch->add(new Bud("bud5"));
        branch->add(new Leaf("leaf6"));
        trunk->add(branch);

        trunk->add(new Leaf("leaf7"));
        trunk->add(new Leaf("leaf8"));

        Component* branch2 = new Composite("branch9");
        branch2->add(new Bud("budA"));
        Component* subComp = new Composite("branchB");
        subComp->add(new Leaf("leafC"));
        branch2->add(subComp);
        trunk->add(branch2);
        branch2->add(new Bud("budD"));
        trunk->add(new Leaf("leafE"));

        trunk->display(1);      // Client code in control of display order.
        cout << endl;

        Leaf* badLeaf = new Leaf("badLeaf");
        badLeaf->add(new Bud("budLeaf"));

        cout << endl;
    }

}
