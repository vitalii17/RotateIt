.pragma library

function create(parent, obj) {
    return Qt.createComponent(obj).createObject(parent)
}
