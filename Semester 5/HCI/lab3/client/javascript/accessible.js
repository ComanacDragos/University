let previousElement = undefined
let previousState = {};

focusedElementState = {
    "border": "5px solid red",
    "transform": "scale(1.3)"

}

let focusables = ally.query.focusable()
let currentFocused = -1


if(focusables.length > 0){
    ally.when.key({
        "shift+right": function(event) {
            currentFocused += 1
            if(currentFocused >= focusables.length)
                currentFocused = 0
            ally.element.focus(focusables[currentFocused])

        },
        "shift+left": function (event){
            currentFocused -= 1
            if(currentFocused <= -1)
                currentFocused = focusables.length-1
            ally.element.focus(focusables[currentFocused])

        }
    });
}

function refreshHandles(){
    focusables = ally.query.focusable()
    for(let i=0;i<focusables.length;i++)
        $(focusables[i]).on('focus', ()=>{
            if(previousElement !== undefined)
                $(previousElement).css(previousState)
            if(i!==currentFocused)
                currentFocused = i

            Object.keys(focusedElementState).forEach(key => previousState[key] = $(focusables[i]).css(key))

            previousElement = focusables[i]
            $(focusables[i]).css(focusedElementState)
        }).on('click', ()=>{
            currentFocused = i
        })
}

refreshHandles()

