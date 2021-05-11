package webubb.domain;

/**
 * Created by forest on 5/17/2018.
 */
public class Asset {
    private int id;
    private int userid;
    private String description;
    private int value;

    public Asset(int id, int userid, String description, int value) {
        this.id = id;
        this.userid = userid;
        this.description = description;
        this.value = value;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getUserid() {
        return userid;
    }

    public void setUserid(int userid) {
        this.userid = userid;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
