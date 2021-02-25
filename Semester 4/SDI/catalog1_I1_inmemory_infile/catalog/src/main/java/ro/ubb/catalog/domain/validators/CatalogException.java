package ro.ubb.catalog.domain.validators;

/**
 * Created by radu.
 */
public class CatalogException extends RuntimeException{

    public CatalogException(String message) {
        super(message);
    }

    public CatalogException(String message, Throwable cause) {
        super(message, cause);
    }

    public CatalogException(Throwable cause) {
        super(cause);
    }
}
