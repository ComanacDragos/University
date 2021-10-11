public class Settings {
    public static int numberOfThreads = 10;
    public static int numberOfProducts = 1000;
    public static int numberOfProductsPerThread = 1000;

    public static Granularity granularity = Granularity.PRODUCT;
    public static boolean moneyLock = true;

    public static  int maxUnitPrice = 10;
    public static int maxAvailableQuantity = 10;

    public static boolean logBill = false;

    public static boolean printProductsAtTheStart = false;
    public static boolean printProductsAtTheEnd = false;
    public static boolean printThreadInfo = false;

    public static int noIterations = 1000;

    public enum Granularity{
        PRODUCT,
        INVENTORY,
        NONE
    }
}
