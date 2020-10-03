package mvc;

public class View {
    Controller controller;
    public View(Controller controller)
    {
        this.controller = controller;
    }

    public void start()
    {
        DynamicVector items = this.controller.itemsHeavierThan(200);
        for(int i=0;i<items.getSize();i+=1)
            System.out.println(items.getItem(i));
    }
}
