function addImage(username, image) {
    const reader = new FileReader();
    console.log("Uploading image...")
    reader.readAsDataURL(image);
    reader.onloadend = function() {
        const base64data = reader.result;
        $.ajax({
            url:"ImagesController",
            type: "post",
            data: {username: username, image: base64data},
            success: () => {
                console.log("Image uploaded")
                getImagesOfUser(username)
            },
            error: () => console.log("Error")
        })
    }
}

/*
<div class="content column">
    <p>Author</p>
    <img src="data:image/jpeg;base64,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">
        <br>
            <div class="row">
                <p>10</p>
                <button>Like</button>
            </div>

</div>
*/

function generateContent(author, image, likes, imageId, username, buttonHandle, buttonText){
    let content = $("<div></div>")
    content.addClass("content column")
    content.append("<p>" + author + "</p>")
    let img = $("<img>")
    img.attr("src", image)
    content.append(img)
    content.append("<br>")
    let row = $("<div></div>")
    row.addClass("row")
    row.append("<p>" + likes + "</p>")
    let button = $("<button>" + buttonText + "</button>")
    button.click((e) => buttonHandle(imageId, username))
    row.append(button)
    content.append(row)
    return content
}

function getImagesOfUser(username){
    $.ajax({
        url:"ImagesController",
        type: "get",
        data: {action: "getImagesOfUser", username: username},
        success: (data) => {
            let images = $("#images")
            images.html("")
            JSON.parse(data).forEach(
                (img) => images.append(generateContent(
                    img.author,
                    img.base64Data,
                    img.likes,
                    img.id,
                    username,
                    dropPhoto,
                    "Drop")
                )
            )
        },
        error: () => console.log("Error")
    })
}

function getAllImages(username){
    const noImages = $("#noImages").val()
    if (noImages === '')
        return
    if(isNaN(noImages)){
        alert("Enter a natural number")
        return
    }
    $.ajax({
        url:"ImagesController",
        type: "get",
        data: {action: "getAllImages", noImages: noImages},
        success: (data) => {
            let images = $("#images")
            images.html("")
            JSON.parse(data).forEach(
                (img) => images.append(generateContent(
                    img.author,
                    img.base64Data,
                    img.likes,
                    img.id,
                    username,
                    likePhoto,
                    "Like")
                )
            )
        },
        error: () => console.log("Error")
    })
}

function likePhoto(imageId, username){
    $.ajax({
        url:"ImagesController" + '?' + $.param({imageId: imageId, username: username}),
        type: "put",
        success: (data) => {
            console.log(data)
            getAllImages(username)
        },
        error: () => console.log("Error")
    })
}

function dropPhoto(imageId, username){
    if(confirm("Are you sure you want to drop the image?"))
        $.ajax({
            url:"ImagesController" + '?' + $.param({imageId: imageId, username: username}),
            type: "delete",
            success: () => {
                console.log("Image dropped")
                getImagesOfUser(username)
            },
            error: () => console.log("Error")
        })
}

function createAccount(){
    $.ajax({
        type : "put",
        url : "LoginController" + '?' + $.param({
            username : $("#newUsername").val(),
            password : $("#newPassword").val(),
            confirmPassword: $("#confirmPassword").val()
        }),
        success: function(data) {
           alert(data)
        }
    });
}
