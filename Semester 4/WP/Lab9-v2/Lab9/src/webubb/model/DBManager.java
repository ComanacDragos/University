package webubb.model;

import webubb.domain.Asset;
import webubb.domain.Image;
import webubb.domain.User;

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
                u = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public void uploadImage(Integer userId, String base64ImageData){
        String sqlCommand = "INSERT INTO images (userId, base64Data) VALUES (?, ?)";
        try (PreparedStatement preparedStatement = con.prepareStatement(sqlCommand)) {
            preparedStatement.setInt(1, userId);
            preparedStatement.setString(2, base64ImageData);
            preparedStatement.executeUpdate();
        } catch (SQLException sqlIntegrityConstraintViolationException) {
            sqlIntegrityConstraintViolationException.printStackTrace();
        }
    }

    public List<Image> getImagesOfUser(Integer userId, String username){
        List<Image> images = new LinkedList<>();
        String sqlCommand = "SELECT * FROM images WHERE userId = ?";

        try (PreparedStatement preparedStatement = con.prepareStatement(sqlCommand);) {
            preparedStatement.setInt(1, userId);
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
}
