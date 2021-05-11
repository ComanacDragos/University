package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Asset;
import webubb.model.DBManager;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;


public class AssetsController extends HttpServlet {
    /*
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if ((action != null) && action.equals("update")) {
            // We update an asset
            Asset asset = new Asset(Integer.parseInt(request.getParameter("id")),
                    Integer.parseInt(request.getParameter("userid")),
                    request.getParameter("description"),
                    Integer.parseInt(request.getParameter("value")));
            DBManager dbmanager = new DBManager();
            Boolean result = dbmanager.updateAsset(asset);
            PrintWriter out = new PrintWriter(response.getOutputStream());
            if (result == true) {
                out.println("Update asset succesfully.");
            } else {
                out.println("Error updating asset!");
            }
            out.flush();
        } else if ((action != null) && action.equals("getAll")) {
            int userid = Integer.parseInt(request.getParameter("userid"));

            response.setContentType("application/json");
            DBManager dbmanager = new DBManager();
            ArrayList<Asset> assets = dbmanager.getUserAssets(userid);
            JSONArray jsonAssets = new JSONArray();
            for (int i = 0; i < assets.size(); i++) {
                JSONObject jObj = new JSONObject();
                jObj.put("id", assets.get(i).getId());
                jObj.put("userid", assets.get(i).getUserid());
                jObj.put("description", assets.get(i).getDescription());
                jObj.put("value", assets.get(i).getValue());
                jsonAssets.add(jObj);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonAssets.toJSONString());
            out.flush();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }*/
}
