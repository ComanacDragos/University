package webubb.model;

import webubb.domain.Asset;
import webubb.domain.Image;
import webubb.domain.User;

import javax.xml.transform.Result;
import java.sql.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class DBManager {
    private Statement stmt;
    private Connection con;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("org.gjt.mm.mysql.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/images", "root", "");
            stmt = con.createStatement();
        } catch(Exception ex) {
            System.out.println("eroare la connect:"+ex.getMessage());
            ex.printStackTrace();
        }
    }

    public User authenticate(String username, String password) {
        ResultSet rs;
        User u = null;
        try {
            rs = stmt.executeQuery("select * from users where username='" + username +"' and password='" + password + "'");
            if (rs.next()) {
                u = new User(rs.getString("username"), rs.getString("password"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public void uploadImage(String username, String base64ImageData){
        String sqlCommand = "INSERT INTO images (username, base64Data) VALUES (?, ?)";
        try (PreparedStatement preparedStatement = con.prepareStatement(sqlCommand)) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, base64ImageData);
            preparedStatement.executeUpdate();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            sqlIntegrityConstraintViolationException.printStackTrace();
        }
    }

    public List<Image> getImagesOfUser(String username){
        List<Image> images = new LinkedList<>();
        String sqlCommand = "SELECT images.id, images.base64Data, images.username, COUNT(i.imageId) as 'likes' " +
                "FROM images INNER JOIN imagelikes i on images.id = i.imageId " +
                "WHERE images.username = ? " +
                "GROUP BY images.id, images.base64Data, images.username " +
                "UNION " +
                "SELECT images.id, images.base64Data, images.username, 0 as 'likes' " +
                "FROM images LEFT JOIN imagelikes i on images.id = i.imageId " +
                "WHERE i.imageId is null and images.username = ? ";

        try (PreparedStatement preparedStatement = con.prepareStatement(sqlCommand);) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, username);
            ResultSet rs = preparedStatement.executeQuery();
            while (rs.next()) {
                Integer id = rs.getInt("id");
                String base64Data = rs.getString("base64Data");
                Integer likes = rs.getInt("likes");
                images.add(
                        new Image(id, likes, username, base64Data)
                );
            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return images;
    }

    public List<Image> getAllImages(Integer noImages){
        List<Image> images = new LinkedList<>();
        String sqlCommand = "SELECT images.id, images.base64Data, images.username, COUNT(i.imageId) as 'likes' " +
                "FROM images INNER JOIN imagelikes i on images.id = i.imageId " +
                "GROUP BY images.id, images.base64Data, images.username " +
                "UNION " +
                "SELECT images.id, images.base64Data, images.username, 0 as 'likes' " +
                "FROM images LEFT JOIN imagelikes i on images.id = i.imageId " +
                "WHERE i.imageId is null";
        sqlCommand = "SELECT t.id, t.base64Data, t.username, t.likes FROM ( " + sqlCommand + " ) t ORDER BY likes DESC LIMIT ?";

        try (PreparedStatement preparedStatement = con.prepareStatement(sqlCommand);) {
            preparedStatement.setInt(1, noImages);
            ResultSet rs = preparedStatement.executeQuery();
            while (rs.next()) {
                Integer id = rs.getInt("id");
                String base64Data = rs.getString("base64Data");
                Integer likes = rs.getInt("likes");
                String username = rs.getString("username");
                images.add(
                        new Image(id, likes, username, base64Data)
                );
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        return images;
    }

    public void dropImage(Integer imageId, String username){
        String sqlCommand = "DELETE FROM images WHERE id = ? && username = ?";
        try (PreparedStatement preparedStatement = con.prepareStatement(sqlCommand)
        ){
            preparedStatement.setInt(1, imageId);
            preparedStatement.setString(2, username);
            preparedStatement.executeUpdate();
        }catch (SQLException exception){
            System.out.println(("Sql exception: " + exception.getMessage()));
        }
    }

    public boolean checkIfUserHasImage(Integer imageId, String username){
        String sqlCommand = "select * from images where id = ? and username = ?";
        return checkImage(imageId, username, sqlCommand);
    }

    public boolean checkIfUserLikedImage(Integer imageId, String username){
        String sqlCommand = "select * from imageLikes where imageId = ? and username = ?";
        return checkImage(imageId, username, sqlCommand);
    }

    private boolean checkImage(Integer imageId, String username, String sqlCommand) {
        try(PreparedStatement preparedStatement = con.prepareStatement(sqlCommand)){
            preparedStatement.setInt(1, imageId);
            preparedStatement.setString(2, username);
            ResultSet rs = preparedStatement.executeQuery();
            return rs.next();
        }
        catch (SQLException exception){
            System.out.println(("Sql exception: " + exception.getMessage()));
            return false;
        }
    }

    public Integer likeImage(Integer imageId, String username){
        String sqlCommand = "INSERT INTO imageLikes (username, imageId) VALUES (?, ?)";
        try(PreparedStatement preparedStatement = con.prepareStatement(sqlCommand)){
            preparedStatement.setString(1, username);
            preparedStatement.setInt(2, imageId);
            return preparedStatement.executeUpdate();
        }
        catch (SQLException exception){
            System.out.println(("Sql exception: " + exception.getMessage()));
            return 0;
        }
    }

    public Integer registerUser(String username, String password){
        String sqlCommand = "INSERT INTO users (username, password) VALUES (?, ?)";
        try(PreparedStatement preparedStatement = con.prepareStatement(sqlCommand)){
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            return preparedStatement.executeUpdate();
        }
        catch (SQLException exception){
            System.out.println(("Sql exception: " + exception.getMessage()));
            return 0;
        }
    }
}
