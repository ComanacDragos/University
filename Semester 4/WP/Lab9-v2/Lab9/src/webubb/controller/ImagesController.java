package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Image;
import webubb.model.DBManager;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class ImagesController extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String image = request.getParameter("image");
        DBManager manager = new DBManager();
        System.out.println(request.getParameter("username") + " -- " + image.getBytes().length);
        manager.uploadImage(request.getParameter("username"), image);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        if (action != null) {
            DBManager manager = new DBManager();
            PrintWriter out = new PrintWriter(response.getOutputStream());
            List<Image> images = new LinkedList<>();
            JSONArray jsonImages = new JSONArray();
            if (action.equals("getImagesOfUser")) {
                String username = request.getParameter("username");
                images = manager.getImagesOfUser(username);
            }
            else if(action.equals("getAllImages")){
                Integer noImages = Integer.parseInt(request.getParameter("noImages"));
                images = manager.getAllImages(noImages);
            }
            images.forEach(
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

    protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int imageId = Integer.parseInt(request.getParameter("imageId"));
        String username = request.getParameter("username");
        System.out.println("Drop photo -- " + imageId + " -- " + username);
        DBManager manager = new DBManager();
        manager.dropImage(imageId, username);
    }

    protected void doPut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int imageId = Integer.parseInt(request.getParameter("imageId"));
        String username = request.getParameter("username");
        System.out.println("Like photo -- " + imageId + " -- " + username);
        DBManager manager = new DBManager();

        PrintWriter out = new PrintWriter(response.getOutputStream());
        if(!manager.checkIfUserHasImage(imageId, username)){
            if(!manager.checkIfUserLikedImage(imageId, username)){
                if(manager.likeImage(imageId, username) != 0){
                    out.println("Image liked");
                }
                else{
                    out.println("Could not like image");
                }
            }else{
                out.println("Image already liked");
            }
        }else{
            out.println("Image of user");
        }
        out.flush();
    }
}
