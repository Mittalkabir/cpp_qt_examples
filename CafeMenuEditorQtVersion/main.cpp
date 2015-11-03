#include <QCoreApplication>
#include <QTextStream>
#include "menuitem.h"
#include "menu.h"
#include "menuiterator.h"
#include "composite.h"
#include "consoleprintmenuvisitor.h"

void createAndPrintMenu()
{
    QTextStream cout(stdout);
    cout << "Restoraunt <<Pizza Celentano>>\n";
    cout << "--------------------------------------------------------\n";

    Menu lMenuMain("MAIN MENU");

    Menu *lPizzaMenu {new Menu{"Pizza Menu"}};
    lPizzaMenu->addSubitem(new MenuItem{"hawaiian pizza", 2.4, "cheese and tomato base with toppings of ham and pineapple"});
    lPizzaMenu->addSubitem(new MenuItem{"vegetarian pizza", 4.2, "cheese and tomato ... "});
    lMenuMain.addSubitem(lPizzaMenu);

    Menu *lBeveragesMenu{new Menu{"Beverages"}};
    lBeveragesMenu->addSubitem(new MenuItem{"Coca-Cola", 2});

    Menu *lCoffeMenu{new Menu{"Coffe"}};
    lCoffeMenu->addSubitem(new MenuItem{"Late", 1, "             "});
    lCoffeMenu->addSubitem(new MenuItem{"Capucino", 2, "             "});
    lBeveragesMenu->addSubitem(lCoffeMenu);

    lBeveragesMenu->addSubitem(new MenuItem{"Pepsi-Cola", 3});

    Menu *lMineralWatersMenu{new Menu{"Mineral waters"}};
    lMineralWatersMenu->addSubitem(new MenuItem{"Borjomi", 2.43, "   nice thing  "});
    lMineralWatersMenu->addSubitem(new MenuItem{"Morshynska", 1.4, "         "});
    lBeveragesMenu->addSubitem(lMineralWatersMenu);

    Menu *lAlcoDrinksMenu {new Menu{"Alco drinks"}};
    Menu *lWinesMenu {new Menu{"Wines"}};
    Menu *lDryWines {new Menu{"Dry Wines"}};
    lDryWines->addSubitem(new MenuItem{"Bordeaux", 20});
    lWinesMenu->addSubitem(lDryWines);
    lWinesMenu->addSubitem(new MenuItem{"Champagne", 16.5});
    lAlcoDrinksMenu->addSubitem(lWinesMenu);
    lAlcoDrinksMenu->addSubitem(new MenuItem{"Beer", 5});
    lBeveragesMenu->addSubitem(lAlcoDrinksMenu);

    lMenuMain.addSubitem(lBeveragesMenu);

    // Iteration example
    MenuIterator it(&lMenuMain);

    // visiting with visitor that prints each item
    ConsolePrintMenuVisitor printVisitor;

    Composite *item{nullptr};
    while (it.hasNext())
    {
        item = it.next();
        if(item)
        {
            item->accept(&printVisitor);
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    createAndPrintMenu();
    return app.exec();
}

