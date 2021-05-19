prevCategory = ""
prevStartDate = ""
prevEndDate = ""

function generateNews(newsData) {
    return `<div class=\"news\">
                <h2>${newsData.title}</h2>
                <p>${newsData.text}</text>
                <p>By ${newsData.producer} on ${newsData.date.split("T")[0]}</p>
                <p>${newsData.category}</p>
            </div>`
}

function refreshNews(news) {
    $("#newsContainer").html("")
    news.map(generateNews).forEach(element => {
        $("#newsContainer").append(element)
    });
}

$("#filterButton").click(
    (e) => {
        $.ajax({
            type : "GET",
            url : "/Main/GetNews", 
            data: {
                category: $("#category").val(),
                startDate: $("#startDate").val(),
                endDate: $("#endDate").val()
                },					
            success: function (data, status) {  
                refreshNews(data)
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

$.ajax({
    type: "GET",
    url: "/Main/GetNews",
    data: {},
    success: function (data, status) {
        refreshNews(data)
    }
});