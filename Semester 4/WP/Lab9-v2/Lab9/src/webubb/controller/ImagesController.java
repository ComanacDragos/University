package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Image;
import webubb.model.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class ImagesController extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String image = request.getParameter("image");
        Integer userId = Integer.parseInt(request.getParameter("userId"));
        DBManager manager = new DBManager();
        manager.uploadImage(userId, image);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if (action != null){
            DBManager manager = new DBManager();
            PrintWriter out = new PrintWriter(response.getOutputStream());
            if (action.equals("getImagesOfUser")) {
                Integer userId = Integer.parseInt(request.getParameter("userId"));
                String username = request.getParameter("username");
                JSONArray jsonImages = new JSONArray();
                manager.getImagesOfUser(userId, username).forEach(
                        (image) -> {
                            JSONObject jObj = new JSONObject();
                            jObj.put("id", image.getId());
                            jObj.put("author", image.getAuthor());
                            jObj.put("base64Data", image.getBase64Data());
                            jObj.put("likes", image.getLikes());
                            jsonImages.add(jObj);
                        }
                );
                out.println(jsonImages.toJSONString());
                out.flush();
            }
        }
    }
}
