var searchParams = new URLSearchParams(window.location.search)
var username = searchParams.get('username')

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
                    alert(JSON.parse(data))
                }
            });  
    }
)

$("#backToNews").css("margin-bottom", "20px")