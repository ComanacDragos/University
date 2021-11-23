let previousElement = undefined
let previousState = {"background-color": undefined};

focusedElementState = {
    "background-color": "red"
}

let focusables = ally.query.focusable()
let currentFocused = -1

if(focusables.length > 0){
    ally.when.key({
        right: function(event) {
            currentFocused += 1
            if(currentFocused >= focusables.length)
                currentFocused = 0
            ally.element.focus(focusables[currentFocused])

        },
        left: function (event){
            currentFocused -= 1
            if(currentFocused <= -1)
                currentFocused = focusables.length-1
            ally.element.focus(focusables[currentFocused])

        }
    });
}

for(let i=0;i<focusables.length;i++)
    $(focusables[i]).on('focus', ()=>{
        if(previousElement !== undefined)
            $(previousElement).css(previousState)
        if(i!==currentFocused)
            currentFocused = i

        previousState["background-color"] = $(focusables[i]).css("background-color")
        previousElement = focusables[i]
        $(focusables[i]).css(focusedElementState)
    }).on('click', ()=>{
        currentFocused = i
    })