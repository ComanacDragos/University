<%@ page import="webubb.domain.User" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Insert title here</title>
    <style>
        .asset-name {
            background-color: cornflowerblue;
            border-right: solid 1px black;
        }
    </style>
    <script src="js/jquery-2.0.3.js"></script>
    <script src="js/ajax-utils.js"></script>
</head>
<body>
asdasddddddasdasdasds
<%! User user; %>
<%  user = (User) session.getAttribute("user");
    if (user != null) {
        out.println("Welcome "+user.getUsername());
%>
        <br/>
        <p><button id="getAssetsbtn" type="button">Get Assets</button></p>
        <section><table id="asset-table"></table></section>
        <p style="height: 50px;"></p>
        <section id="update-section">
            <span style="font-weight: bold; background-color: mediumseagreen">Update asset</span><br/>
            <table>
                <tr><td>ID asset: </td><td><input type="text" id="asset-id"></td></tr>
                <tr><td>Asset userid: </td><td><input type="text" id="asset-userid"></td></tr>
                <tr><td>Asset description: </td><td><input type="text" id="asset-description"></td></tr>
                <tr><td>Asset value: </td><td><input type="text" id="asset-value"></td></tr>
                <tr><td><button type="button" id="update-asset-btn">Update asset</button></td><td></td></tr>
            </table>
        </section>
        <section id="update-result-section"></section>


        <script>
            $(document).ready(function(){
                $("#getAssetsbtn").click(function() {
                    getUserAssets(<%= user.getId() %>, function(assets) {
                        console.log(assets);
                        $("#asset-table").html("");
                        $("#asset-table").append("<tr style='background-color: mediumseagreen'><td>Id</td><td>Userid</td><td>Description</td><td>Value</td></tr>");
                        for(var name in assets) {
                            //console.log(assets[name].description);
                            $("#asset-table").append("<tr><td class='asset-name'>"+assets[name].id+"</td>" +
                                "<td>"+assets[name].userid+"</td>" +
                                "<td>"+assets[name].description+"</td>" +
                                "<td>"+assets[name].value+"</td></tr>");
                        }
                    })
                })

                $("#update-asset-btn").click(function() {
                    updateAsset($("#asset-id").val(),
                        $("#asset-userid").val(),
                        $("#asset-description").val(),
                        $("#asset-value").val(),
                        function(response) {
                            $("#update-result-section").html(response);
                        }
                    )
                })

            });
        </script>
<%
    }
%>

</body>
</html>
