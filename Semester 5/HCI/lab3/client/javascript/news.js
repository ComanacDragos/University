var searchParams = new URLSearchParams(window.location.search)
var username = searchParams.get('username')

prevCategory = ""
prevStartDate = ""
prevEndDate = ""

$.ajax({
    type : "GET",
    url : "http://localhost:3000/controller.php",
    data: {action: "getLoggedUser", username: username},					
        success: function(data, status) {
            if(JSON.parse(data) || JSON.parse(data) === ""){
                let username = JSON.parse(data)
                $("#welcome").text((i, oldText)=>{
                    if(username != "")
                        return "Welcome " + username  + "!"
                    return "Welcome guest!"
                }) 
                
                if(username === ""){
                    let links = $("header nav").children()
                    links[0].text = "Back to login"
                    links[1].remove()
                    links[2].remove()
                }
            }
            else{
                window.location.replace("index.html")
            }
        }
});


function generateNews(newsData){
    return `<div class=\"news\">
                <h2>${newsData['title']}</h2>
                <p>${newsData['text']}</text>
                <p>By ${newsData['producer']} on ${newsData['date']}</p>
                <p>${newsData['category']}</p>
            </div>`
}

function refreshNews(news){
    $("#newsContainer").html("")
    news.map(generateNews).forEach(element => {
        $("#newsContainer").append(element)    
    });
}

$.ajax({
    type : "GET",
    url : "http://localhost:3000/controller.php",
    data: {action: "getNews"},					
        success: function(data, status) {
            refreshNews(JSON.parse(data))
        }
});

$("#addNews").click(
    (e)=>{
        e.preventDefault()
        window.location.replace("addNews.html?username=" + username)
    }
)

$("#filterButton").click(
    (e) =>{
        $.ajax({
            type : "GET",
            url : "http://localhost:3000/controller.php",
            data: {
                action: "getFilteredNews",
                category: $("#category").val(),
                startDate: $("#startDate").val(),
                endDate: $("#endDate").val()
                },					
                success: function(data, status) {
                    refreshNews(JSON.parse(data))
                    $("#prevCategory").text((i, oldText)=>{
                        return "Category: " + prevCategory
                    })
                    $("#prevStartDate").text((i, oldText)=>{
                        return "Start Date: " + prevStartDate
                    })
                    $("#prevEndDate").text((i, oldText)=>{
                        return "End Date: " + prevEndDate
                    })

                    prevCategory = $("#category").val()
                    prevStartDate = $("#startDate").val()
                    prevEndDate = $("#endDate").val()
                }
        });
    }
)

$("#changePassword").click(
    (e)=>{
        window.location.replace("changePassword.html?username=" + username)
    }
)

