package webubb.domain;

public class Image {
    private Integer id, likes;
    private String author, base64Data;

    public Image(Integer id, Integer likes, String author, String base64Data) {
        this.id = id;
        this.likes = likes;
        this.author = author;
        this.base64Data = base64Data;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getLikes() {
        return likes;
    }

    public void setLikes(Integer likes) {
        this.likes = likes;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getBase64Data() {
        return base64Data;
    }

    public void setBase64Data(String base64Data) {
        this.base64Data = base64Data;
    }
}
