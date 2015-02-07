/* Consider modeling a fruit tree. Branches can contain other branches or leaves.
* Of course they can also contain buds, and eventually fruit.
* Rewrite the problematic example below to follow the open-closed principle.
* See if you can get the number of seam points in the library code down to just one.
*
* Extra Credit:
*   What happens when the spec change occurs to allow removing branches and leaves?
*   Who is in control of the display order?
*   Add the fruit class to both the problem and the design pattern code. Can you see the difference in maintainability?
*/

#include <list>
#include <iostream>
#include <string>

// ************************ Original Spec ************************
namespace leaf_versus_list {

    class Leaf;
    class Bud;
    class Fruit;
    // Seam point 1: Add class declaration for fruit.

    class Branch {    // Has to be changed for new types of 'leaves' - violates open-closed principle.
    public:
        std::string name;
        std::list<Branch*> branches;
        std::list<Leaf*>   leafs;
        std::list<Bud*>    buds;
        std::list<Fruit*>  fruits;
        // Seam point 2: Add container for fruit.
    public:
        Branch(std::string name) : name(name) {}
    public:
        void addBranch(Branch* branch) {
            branches.push_back(branch);
        }
        void addLeaf(Leaf* leaf) {
            leafs.push_back(leaf);
        }
        void addBud(Bud* bud) {
            buds.push_back(bud);
        }
        void addFruit(Fruit* fruit) {
            fruits.push_back(fruit);
        }
        // Seam point 3: Add add method for fruit.
    };

    class Leaf {
    public:
        std::string name;
    public:
        Leaf(std::string name) : name(name) {}
    };

    class Bud {
    public:
        std::string name;
    public:
        Bud(std::string name) : name(name) {}
    };

    class Fruit {
    public:
        std::string name;
    public:
        Fruit(std::string name) : name(name) {}
    };
    // Seam point 4: Add class for fruit.

    void display(Branch* branch, int depth) { // Has to be changed for new types of 'leaves' - violates open-closed principle.
        for (int i = 0; i < depth; i++) std::cout << "-";               // Display this branch.
        std::cout << " " << branch->name << std::endl;

        std::list<Branch*>::iterator it = branch->branches.begin();      // Display all the child branches.
        for (; it != branch->branches.end(); it++) {
            display(*it, depth + 2);
        }

        std::list<Leaf*>::iterator itl = branch->leafs.begin();          // Display all the child leafs.
        for (; itl != branch->leafs.end(); itl++) {
            for (int i = 0; i < depth + 2; i++) std::cout << "-";
            std::cout << " " << (*itl)->name << std::endl;
        }

        std::list<Bud*>::iterator itb = branch->buds.begin();            // Display all the child buds.
        for (; itb != branch->buds.end(); itb++) {
            for (int i = 0; i < depth + 2; i++) std::cout << "-";
            std::cout << " " << (*itb)->name << std::endl;
        }

        std::list<Fruit*>::iterator itf = branch->fruits.begin();            // Display all the child buds.
        for (; itf != branch->fruits.end(); itf++) {
            for (int i = 0; i < depth + 2; i++) std::cout << "-";
            std::cout << " " << (*itf)->name << std::endl;
        }
        // Seam point 5: Add display code for fruit.
    }

    void demo() {
        std::cout << "<< Composite problem >>\n";

        Branch* trunk = new Branch("trunk");
        trunk->addLeaf(new Leaf("leaf1"));
        trunk->addBud(new Bud("bud2"));
        trunk->addLeaf(new Leaf("leaf3"));

        Branch* branch = new Branch("branch4");
        trunk->addBud(new Bud("bud5"));
        branch->addLeaf(new Leaf("leaf6"));
        trunk->addBranch(branch);

        branch->addLeaf(new Leaf("leaf7"));
        branch->addLeaf(new Leaf("leaf8"));

        Branch* branch2 = new Branch("branch9");
        branch2->addLeaf(new Leaf("budA"));
        Branch* subComp = new Branch("branchB");
        subComp->addLeaf(new Leaf("leafC"));
        branch2->addBranch(subComp);
        trunk->addBranch(branch2);
        branch2->addBud(new Bud("budD"));
        trunk->addLeaf(new Leaf("leafE"));

        trunk->addFruit(new Fruit("First Fruit Ever"));

        display(trunk, 1);      // Display order driven by library code, not client code.

        std::cout << std::endl;
    }

}
namespace composite {

    // -------------------------- Component --------------------------
    class TreeComponent {
    public:
        virtual void addSubComponent(TreeComponent* newComponent);
        virtual void display(TreeComponent* startComponent, int depth);

        std::string name;
        TreeComponent(){};
        TreeComponent(std::string name) : name(name){};
    };
    void TreeComponent::addSubComponent(TreeComponent* newComponent){}
    void TreeComponent::display(TreeComponent* startComponent, int depth){  //no need for start Component.!!
        for (int i = 0; i < depth; i++) std::cout << "-";               // Display this component
        std::cout << " " << this->name << std::endl;
    }

    // -------------------------- Composite --------------------------
    class Branch : public TreeComponent {
    public:
        std::list<TreeComponent*> subComponent;
        
        virtual void addSubComponent(TreeComponent* newComponent);
        virtual void display(TreeComponent* startComponent, int depth);

        Branch(std::string name) : TreeComponent(name){};
    };
    void Branch::addSubComponent(TreeComponent* newComponent){
        this->subComponent.push_back(newComponent);
    }
    void Branch::display(TreeComponent* startComponent, int depth){
        for (int i = 0; i < depth; i++) std::cout << "-";               // Display this component
        std::cout << " " << this->name << std::endl;

        for (std::list<TreeComponent*>::iterator it = this->subComponent.begin(); it != this->subComponent.end(); it++){
            (*it)->display(*it, depth + 2);
        }
    }

    class Leaf : public TreeComponent {
    public:
        Leaf(std::string name) : TreeComponent(name){};
    };

    class Bud : public TreeComponent {
    public:
        Bud(std::string name) : TreeComponent(name){};
    };

    class Fruit : public TreeComponent {
    public:
        Fruit(std::string name) : TreeComponent(name){};
    };

    // demo
    void demo() {
        std::cout << "<< With Composite Pattern >>\n";

        Branch* trunk = new Branch("trunk");
        trunk->addSubComponent(new Leaf("leaf1"));
        trunk->addSubComponent(new Bud("bud2"));
        trunk->addSubComponent(new Leaf("leaf3"));

        Branch* branch = new Branch("branch4");
        trunk->addSubComponent(new Bud("bud5"));
        branch->addSubComponent(new Leaf("leaf6"));
        trunk->addSubComponent(branch);

        branch->addSubComponent(new Leaf("leaf7"));
        branch->addSubComponent(new Leaf("leaf8"));

        Branch* branch2 = new Branch("branch9");
        branch2->addSubComponent(new Leaf("budA"));
        Branch* subComp = new Branch("branchB");
        subComp->addSubComponent(new Leaf("leafC"));
        branch2->addSubComponent(subComp);
        trunk->addSubComponent(branch2);
        branch2->addSubComponent(new Bud("budD"));
        trunk->addSubComponent(new Leaf("leafE"));

        trunk->addSubComponent(new Fruit("First Fruit Ever"));

        trunk->display(trunk, 1);      // Display order driven client code. and depth first search

        std::cout << std::endl;
    }
}

// ************************ Spec changed to allow remove operation ************************
namespace leaf_versus_list_removable {

    class Leaf;
    class Bud;
    class Fruit;
    // Seam point 1: Add class declaration for fruit.

    class Branch {    // Has to be changed for new types of 'leaves' - violates open-closed principle.
    public:
        std::string name;
        std::list<Branch*> branches;
        std::list<Leaf*>   leafs;
        std::list<Bud*>    buds;
        std::list<Fruit*>  fruits;
        // Seam point 2: Add container for fruit.
    public:
        Branch(std::string name) : name(name) {}
    public:
        void addBranch(Branch* branch) {
            branches.push_back(branch);
        }
        void addLeaf(Leaf* leaf) {
            leafs.push_back(leaf);
        }
        void addBud(Bud* bud) {
            buds.push_back(bud);
        }
        void addFruit(Fruit* fruit) {
            fruits.push_back(fruit);
        }
        // Seam point 3: Add add method for fruit.

        void removeBranch(Branch* branch) {
            branches.remove(branch);
        };
        void removeLeaf(Leaf* leaf) {
            leafs.remove(leaf);
        };
        void removeBud(Bud* bud) {
            buds.remove(bud);
        };
        void removeFruit(Fruit* fruit) {
            fruits.remove(fruit);
        };
    };

    class Leaf {
    public:
        std::string name;
    public:
        Leaf(std::string name) : name(name) {}
    };

    class Bud {
    public:
        std::string name;
    public:
        Bud(std::string name) : name(name) {}
    };

    class Fruit {
    public:
        std::string name;
    public:
        Fruit(std::string name) : name(name) {}
    };
    // Seam point 4: Add class for fruit.

    void display(Branch* branch, int depth) { // Has to be changed for new types of 'leaves' - violates open-closed principle.
        for (int i = 0; i < depth; i++) std::cout << "-";               // Display this branch.
        std::cout << " " << branch->name << std::endl;

        std::list<Branch*>::iterator it = branch->branches.begin();      // Display all the child branches.
        for (; it != branch->branches.end(); it++) {
            display(*it, depth + 2);
        }

        std::list<Leaf*>::iterator itl = branch->leafs.begin();          // Display all the child leafs.
        for (; itl != branch->leafs.end(); itl++) {
            for (int i = 0; i < depth + 2; i++) std::cout << "-";
            std::cout << " " << (*itl)->name << std::endl;
        }

        std::list<Bud*>::iterator itb = branch->buds.begin();            // Display all the child buds.
        for (; itb != branch->buds.end(); itb++) {
            for (int i = 0; i < depth + 2; i++) std::cout << "-";
            std::cout << " " << (*itb)->name << std::endl;
        }

        std::list<Fruit*>::iterator itf = branch->fruits.begin();            // Display all the child buds.
        for (; itf != branch->fruits.end(); itf++) {
            for (int i = 0; i < depth + 2; i++) std::cout << "-";
            std::cout << " " << (*itf)->name << std::endl;
        }
        // Seam point 5: Add display code for fruit.
    }

    void demo() {
        std::cout << "<< Composite problem >>\n";

        Branch* trunk = new Branch("trunk");
        trunk->addLeaf(new Leaf("leaf1"));
        trunk->addBud(new Bud("bud2"));
        Leaf* toBeRemovedLeaf = NULL;
        trunk->addLeaf(toBeRemovedLeaf = new Leaf("leaf3"));

        Branch* branch = new Branch("branch4");
        Bud* toBeRemovedBud = NULL;
        trunk->addBud(toBeRemovedBud = new Bud("bud5"));
        branch->addLeaf(new Leaf("leaf6"));
        trunk->addBranch(branch);

        branch->addLeaf(new Leaf("leaf7"));
        branch->addLeaf(new Leaf("leaf8"));

        Branch* branch2 = new Branch("branch9");
        branch2->addLeaf(new Leaf("budA"));
        Branch* subComp = new Branch("branchB");
        subComp->addLeaf(new Leaf("leafC"));
        branch2->addBranch(subComp);
        trunk->addBranch(branch2);
        branch2->addBud(new Bud("budD"));
        trunk->addLeaf(new Leaf("leafE"));

        trunk->addFruit(new Fruit("First Fruit Ever"));

        display(trunk, 1);      // Display order driven by library code, not client code.

        std::cout << std::endl;

        std::cout << "<< Delete branchB, leaf3, bud5 >>\n";
        branch2->removeBranch(subComp);
        trunk->removeLeaf(toBeRemovedLeaf);
        trunk->removeBud(toBeRemovedBud);

        display(trunk, 1);
    }

}
namespace composite_removable {

    // -------------------------- Component --------------------------
    class TreeComponent {
    public:
        virtual void addSubComponent(TreeComponent* newComponent);
        virtual void removeSubComponent(TreeComponent* toBeRemoved);
        virtual void display(TreeComponent* startComponent, int depth);

        std::string name;
        TreeComponent(){};
        TreeComponent(std::string name) : name(name){};
    };
    void TreeComponent::addSubComponent(TreeComponent* newComponent){}
    void TreeComponent::removeSubComponent(TreeComponent* toBeRemoved){}
    void TreeComponent::display(TreeComponent* startComponent, int depth){
        for (int i = 0; i < depth; i++) std::cout << "-";               // Display this component
        std::cout << " " << this->name << std::endl;
    }

    // -------------------------- Composite --------------------------
    class Branch : public TreeComponent {
    public:
        std::list<TreeComponent*> subComponent;

        virtual void addSubComponent(TreeComponent* newComponent);
        virtual void removeSubComponent(TreeComponent* newComponent);
        virtual void display(TreeComponent* startComponent, int depth);

        Branch(std::string name) : TreeComponent(name){};
    };
    void Branch::addSubComponent(TreeComponent* newComponent){
        this->subComponent.push_back(newComponent);
    }
    void Branch::removeSubComponent(TreeComponent* toBeRemoved){
        this->subComponent.remove(toBeRemoved);
    }
    void Branch::display(TreeComponent* startComponent, int depth){
        for (int i = 0; i < depth; i++) std::cout << "-";               // Display this component
        std::cout << " " << this->name << std::endl;

        for (std::list<TreeComponent*>::iterator it = this->subComponent.begin(); it != this->subComponent.end(); it++){
            (*it)->display(*it, depth + 2);
        }
    }

    class Leaf : public TreeComponent {
    public:
        Leaf(std::string name) : TreeComponent(name){};
    };

    class Bud : public TreeComponent {
    public:
        Bud(std::string name) : TreeComponent(name){};
    };

    class Fruit : public TreeComponent {
    public:
        Fruit(std::string name) : TreeComponent(name){};
    };

    // demo
    void demo() {
        std::cout << "<< With Composite Pattern >>\n";

        Branch* trunk = new Branch("trunk");
        trunk->addSubComponent(new Leaf("leaf1"));
        trunk->addSubComponent(new Bud("bud2"));
        Leaf* toBeRemovedLeaf = NULL;
        trunk->addSubComponent(toBeRemovedLeaf = new Leaf("leaf3"));

        Branch* branch = new Branch("branch4");
        Bud* toBeRemovedBud = NULL;
        trunk->addSubComponent(toBeRemovedBud = new Bud("bud5"));
        branch->addSubComponent(new Leaf("leaf6"));
        trunk->addSubComponent(branch);

        branch->addSubComponent(new Leaf("leaf7"));
        branch->addSubComponent(new Leaf("leaf8"));

        Branch* branch2 = new Branch("branch9");
        branch2->addSubComponent(new Leaf("budA"));
        Branch* subComp = new Branch("branchB");
        subComp->addSubComponent(new Leaf("leafC"));
        branch2->addSubComponent(subComp);
        trunk->addSubComponent(branch2);
        branch2->addSubComponent(new Bud("budD"));
        trunk->addSubComponent(new Leaf("leafE"));

        trunk->addSubComponent(new Fruit("First Fruit Ever"));

        trunk->display(trunk, 1);      // Display order driven client code. and depth first search

        std::cout << std::endl;

        std::cout << "<< Delete branchB, leaf3, bud5 >>\n";
        branch2->removeSubComponent(subComp);
        trunk->removeSubComponent(toBeRemovedLeaf);
        trunk->removeSubComponent(toBeRemovedBud);

        trunk->display(trunk, 1);
    }
}


int main(){
    leaf_versus_list::demo();
    composite::demo();
    //leaf_versus_list_removable::demo();
    //std::cout << "\n\n--------------------------\n\n";
    //composite_removable::demo();
    return 0;
}