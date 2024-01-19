const inside_view = (process_order) => {
  const variable_enumeration_list_keys = Object.keys(meta_data.variable_enumeration);

  const inside_view_element = document.getElementById("inside_view_container");
  if (!inside_view_element) {
    return;
  }

  while (inside_view_element.firstChild) {
    inside_view_element.removeChild(inside_view_element.firstChild);
  }

  console.log(variable_enumeration_list_keys);

  for (let i = 0; i < variable_enumeration_list_keys.length; i++) {
    const layer = variable_enumeration_list_keys[i];
    const variable_enumeration_data = meta_data.variable_enumeration[layer];

    const variable_inside = confirmVariable(process_order, layer);
    console.log("variable_inside" + variable_inside);
    const element_insideview_block = buildInsideBlock(process_order, variable_enumeration_data);
    inside_view_element.appendChild(element_insideview_block);

    if (variable_enumeration_data.type == "int") {
      buildInsideVariable(element_insideview_block, process_order, variable_inside, variable_enumeration_data);
      continue;
    }

    if (variable_enumeration_data.type == "string") {
      buildInsideVariable(element_insideview_block, process_order, variable_inside, variable_enumeration_data);
      continue;
    }

    if (variable_enumeration_data.type == "pointer") {
      buildInsideArray(element_insideview_block, process_order, variable_inside, variable_enumeration_data);
    }
  }
};

// 最終更新の変数を検知する
//process_order 対象process_order
//layer
const confirmVariable = (process_order, layer) => {
  for (let i = 0; i <= process_order; i++) {
    let li = process_order - i;

    if (layer in process_data[li].variable) {
      return process_data[li].variable[layer];
    }
  }
  return "value-undefined";
};

// 最終更新の変数を検知する
//process_order 対象process_order
//layer
const confirmPointer = (process_order, layer) => {
  for (let i = 0; i <= process_order; i++) {
    let li = process_order - i;

    if (layer in process_data[li].pointer) {
      return process_data[li].pointer[layer];
    }
  }
  return "value-undefined";
};

//ベースとなるDOM要素を構築する。この子ノードに変数表示をする
//process_order 対象process_order
const buildInsideBlock = (process_order, variable_enumeration_data) => {
  const element_insideview_block = document.createElement("div");
  element_insideview_block.className = "inside_view_block";

  return element_insideview_block;
};

//ベースとなるDOM要素をの子要素に、変数を追加する
//process_order
//variable_enumeration_data
//variable_inside
//variable_enumeration_data
const buildInsideVariable = (element_insideview_block, process_order, variable_inside, variable_enumeration_data) => {
  const element_insideview_variable_block = document.createElement("div");
  element_insideview_variable_block.className = "inside_view_block_value";
  element_insideview_block.appendChild(element_insideview_variable_block);

  const inside_view_value_name = document.createElement("div");
  inside_view_value_name.className = "inside_view_block_value_name";
  inside_view_value_name.innerText = variable_enumeration_data.name;
  element_insideview_variable_block.appendChild(inside_view_value_name);

  const inside_view_value_data = document.createElement("div");
  inside_view_value_data.className = "inside_view_block_value_data";
  inside_view_value_data.innerText = variable_inside;
  element_insideview_variable_block.appendChild(inside_view_value_data);
};

const buildInsideArray = (element_insideview_block, process_order, variable_inside, variable_enumeration_data) => {
  const element_insideview_variable_block = document.createElement("div");
  element_insideview_variable_block.className = "inside_view_block_array";
  element_insideview_block.appendChild(element_insideview_variable_block);

  const inside_view_value_name = document.createElement("div");
  inside_view_value_name.className = "inside_view_block_array_name";
  inside_view_value_name.innerText = variable_enumeration_data.name;
  element_insideview_variable_block.appendChild(inside_view_value_name);

  const inside_view_value_data = document.createElement("div");
  inside_view_value_data.className = "inside_view_block_array_data";
  element_insideview_variable_block.appendChild(inside_view_value_data);

  recursionBuildInsideArray(inside_view_value_data, process_order, variable_inside, variable_enumeration_data);
};

const recursionBuildInsideArray = (element_insideview_block, process_order, variable_inside, variable_enumeration_data) => {
  const pointer_inside_array = confirmPointer(process_order, variable_inside); //これは配列
  if (pointer_inside_array == "value-undefined") {
    buildInsideArrayBlock(element_insideview_block, process_order, variable_inside, variable_enumeration_data);
    return 0;
  }

  const inside_view_value_data = document.createElement("div");
  inside_view_value_data.className = "inside_view_block_array_data_line";
  element_insideview_block.appendChild(inside_view_value_data);

  let depth;
  for (let i = 0; i < pointer_inside_array.length; i++) {
    const pointer_inside = pointer_inside_array[i];
    depth = recursionBuildInsideArray(inside_view_value_data, process_order, pointer_inside, variable_enumeration_data);
  }

  if (depth % 2 == 1) {
    inside_view_value_data.className = "inside_view_block_array_data_column";
  }

  return depth + 1;
};

const buildInsideArrayBlock = (element_insideview_block, process_order, pointer_inside, variable_enumeration_data) => {
  const inside_view_value_data = document.createElement("div");
  inside_view_value_data.className = "inside_view_block_array_data_block";

  const variable_inside = confirmVariable(process_order, pointer_inside);
  inside_view_value_data.innerText = variable_inside;
  element_insideview_block.appendChild(inside_view_value_data);

  console.log(variable_inside);
};
