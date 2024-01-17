
let codeview_states = [];
let timeline_states = [];

let focus_process = -1;

const getTokenElement = (order) =>{
    const text = "token" + order;
    const token_element = document.getElementById(text);

    console.log(text , token_element)
    return token_element;
}

const getProcessElement = (order) =>{
    const text = "process" + order;
    const token_element = document.getElementById(text);
    return token_element;
}

class State{
    constructor(order,state_type){
        this.order = order;
        this.state_type = state_type;

        this.dom_name_list = [];
        this.dom_name_added_list = [];
    }
    setHtmlClass(name){
        this.dom_name_list.push(name);
        this.dom_name_added_list.push(name);
        const element = this.state_type == "token" ? getTokenElement (this.order) : getProcessElement(this.order);
        element.classList.add(name);
    }

    allRemoveHtmlClass(){
        for (let i = 0; i < this.dom_name_added_list.length ; i++){
            const added = this.dom_name_added_list[i];
            this.removeHtmlClass(added);
        }
    }
    removeHtmlClass(name){
        if(!(this.dom_name_added_list.includes(name))){
            return
        }
        this.dom_name_added_list = this.dom_name_added_list.filter(n => n != name);
        const element = this.state_type == "token" ? getTokenElement (this.order) : getProcessElement(this.order);
        element.classList.remove(name);
    }
}

console.log(codeview_states);
console.log(timeline_states);

for (let i = 0 ; i < meta_data.token_length ; i++){
    codeview_states[i] = new State(i,"token");
}

for (let i = 0 ; i < meta_data.process_length ; i++){
    timeline_states[i] = new State(i,"process");
}

const resetCodeViewState = () => {
    for (let i = 0 ; i < codeview_states.length ; i++){
        codeview_states[i].allRemoveHtmlClass();
    }
}

const resetTimelineState = () => {
    for (let i = 0 ; i < timeline_states.length ; i++){
        timeline_states[i].allRemoveHtmlClass();
    }
}

const resetCodeViewStateName = (name) => {
    for (let i = 0 ; i < codeview_states.length ; i++){
        codeview_states[i].removeHtmlClass(name);
    }
}

const resetTimelineStateName = (name) => {
    for (let i = 0 ; i < timeline_states.length ; i++){
        timeline_states[i].removeHtmlClass(name);
    }
}

const processOrderToTokenOrder = (process_order) => {
    const process = process_data[process_order];
    const token_order = process.token_order;
    return token_order;
}

const messageClick = (process_order) => {
    const token_order = processOrderToTokenOrder(process_order);
    resetCodeViewStateName("linking");
    resetTimelineStateName("linking");
    codeview_states[token_order].setHtmlClass("linking");
    timeline_states[process_order].setHtmlClass("linking");
    console.log(codeview_states[token_order]);
    focus_process = process_order;
};


const messageHover = (process_order) => {
    const token_order = processOrderToTokenOrder(process_order);
    resetCodeViewStateName("timeline_hover");
    resetTimelineStateName("timeline_hover");

    codeview_states[token_order].setHtmlClass("timeline_hover");
    timeline_states[process_order].setHtmlClass("timeline_hover");
    console.log(codeview_states[token_order]);
};

const messageHoverOut = (process_order) => {
    const token_order = processOrderToTokenOrder(process_order);
    resetCodeViewStateName("timeline_hover");
    resetTimelineStateName("timeline_hover");

    console.log(codeview_states[token_order]);
};

const process_back = () => {
    focus_process = Math.max(focus_process - 1 , 0);
    messageClick(focus_process);
}
const process_next = () => {
    focus_process = Math.min(focus_process + 1 , meta_data.process_length - 1);
    messageClick(focus_process);
}