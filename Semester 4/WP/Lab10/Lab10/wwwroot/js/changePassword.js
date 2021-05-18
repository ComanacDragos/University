var searchParams = new URLSearchParams(window.location.search)
var username = searchParams.get('username')

$.ajax({
    type : "GET",
    url : "http://localhost:3000/Lab7/server/controller.php", 
    data: {action: "getLoggedUser", username: username},					
        success: function(data, status) {
            if(!JSON.parse(data)){
                window.location.replace("index.html")
            }
        }
});

$("#backToNews").click(
    (e) =>{
        window.location.replace("news.html?username=" + username)
    }
)

$("#changePasswordButton").click(
    (e) =>{
        $.ajax({
            type : "GET",
            url : "http://localhost:3000/Lab7/server/controller.php", 
            data: {
                action: "changePassword", 
                username : username, 
                password : $("#newPassword").val(),
                confirmPassword: $("#confirmPassword").val(),
                oldPassword: $("#oldPassword").val()
            },					
                success: function(data, status) {
                    console.log(data)
                    tokens = JSON.parse(data)
                    if(tokens[0]){
                        window.location.replace("changePassword.html?username=" + tokens[1])
                        alert("Password changed successfuly!")
                    }else{
                        alert(tokens[1])
                    }
                }
            });  
    }
)

$("#backToNews").css("margin-bottom", "20px")