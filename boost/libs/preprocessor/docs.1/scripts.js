function init(id) {
	document.getElementById(id).style.display = "none";
	return;
}

function toggle(id) {
	var x = document.getElementById(id);
	x.style.display = x.style.display == "none" ? "block" : "none";
	return;
}

function change(obj) {
	obj.style.textDecoration = "underline";
	obj.style.cursor = "hand";
	obj.style.cursor = "pointer";
	obj.style.color = "orange";
	return;
}

function revert(obj) {
	obj.style.textDecoration = "none";
	obj.style.color = "black";
	return;
}
