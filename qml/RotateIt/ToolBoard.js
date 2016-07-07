
var items = [];

function calcFreeWidth(columns) {
    var itemWidth = items[0].width;
    return root.width - root.leftPadding - root.rightPadding - (columns - 1) *
            (itemWidth + root.spacing) - itemWidth;
}

function layout() {
    if(root.width === 0) return;
    if(items.length < 1) return;

    var itemWidth  = items[0].width;
    var itemHeight = items[0].height;

    var maxColumns = Math.floor((root.width - root.leftPadding -
                                 root.rightPadding - itemWidth) /
                                (itemWidth + root.spacing) + 1);
    if(maxColumns < 1) return;

    var columns = (items.length <= maxColumns) ? items.length : maxColumns;
    var rows   = (items.length > maxColumns) ? Math.ceil(items.length / columns) : 1;

    root.height = root.topPadding + root.bottomPadding +
            (rows - 1) * (root.spacing + itemHeight) + itemHeight;

    var currentItem = 0;
    var columnsInRow;

    for(var row = 0; row < rows; row++) {
        for(var column = 0; column < maxColumns; column++) {

            columnsInRow = ((rows - row - 1) === 0) ? (items.length - columns *
                                                  (rows - 1)) :
                                                 columns;

            items[currentItem].x = calcFreeWidth(columnsInRow) / 2 +
                    column * (itemWidth + root.spacing) +
                    root.leftPadding;

            items[currentItem].y = root.topPadding + row * (itemHeight + root.spacing);

            currentItem++;
            if(currentItem === items.length) break;
        }
    }
}


