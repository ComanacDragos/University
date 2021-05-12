package webubb.controller;

import webubb.domain.User;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class PageController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String page = request.getParameter("page");
        System.out.println(((User)request.getSession().getAttribute("user")).getUsername() + " -- " + page);
        RequestDispatcher rd;
        rd = request.getRequestDispatcher(page);
        rd.forward(request, response);
    }
}
