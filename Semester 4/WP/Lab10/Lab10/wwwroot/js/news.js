prevCategory = ""
prevStartDate = ""
prevEndDate = ""


$("#filterButton").click(
    (e) =>{
        $.ajax({
            type : "GET",
            url : "/Main/FilterNews", 
            data: {
                category: $("#category").val(),
                startDate: $("#startDate").val(),
                endDate: $("#endDate").val()
                },					
                success: function(data, status) {
                    console.log(data)
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
