$("#changePasswordButton").click(
    (e) =>{
        $.ajax({
            type : "GET",
            url : "/Main/UpdatePassword", 
            data: {
                newPassword : $("#newPassword").val(),
                confirmPassword: $("#confirmPassword").val(),
                oldPassword: $("#oldPassword").val()
            },					
            success: function (data, status) {
                $("#message").html(data)
            }
        });  
    }
)