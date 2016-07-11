var test1:Number;// numbers to use to test for overlap
var test2:Number;

var testNum:Number; // number to test if its the new max/min

var min1:Number; //current smallest(shape 1)
var max1:Number;//current largest(shape 1)

var min2:Number;//current smallest(shape 2)
var max2:Number;//current largest(shape 2)

var axis:Vector2D;//the normal axis for projection
var offset:Number;

var vectorOffset:Vector2D;
var vectors1    :Vector.<Vector2D>;//the points
var vectors2    :Vector.<Vector2D>;//the points

vectors1 = polygon1.vertices.concat();//these functions are in my polygon class, all they do is return a Vector.<Vector2D> of the vertices of the polygon
vectors2 = polygon2.vertices.concat();

// add a little padding to make the test work correctly
if (vectors1.length == 2) {
	var temp:Vector2D = new Vector2D(-(vectors1[1].y - vectors1[0].y), vectors1[1].x - vectors1[0].x);
	temp.truncate(0.0000000001);
	vectors1.push(vectors1[1].add(temp));
}

if (vectors2.length == 2) {
	temp = new Vector2D(-(vectors2[1].y - vectors2[0].y), vectors2[1].x - vectors2[0].x);
	temp.truncate(0.0000000001);
	vectors2.push(vectors2[1].add(temp));
}

// find vertical offset
vectorOffset= new Vector2D(polygon1.x - polygon2.x, polygon1.y - polygon2.y);

// loop to begin projection
for (var i:int = 0; i < vectors1.length; i++) {

	// get the normal axis, and begin projection
	axis = findNormalAxis(vectors1, i);
	
	// project polygon1
	min1 = axis.dotProduct(vectors1[0]);
	max1 = min1;//set max and min equal

	for (var j:int = 1; j < vectors1.length; j++) {
		testNum = axis.dotProduct(vectors1[j]);//project each point
		if (testNum < min1) min1 = testNum;//test for new smallest
		if (testNum > max1) max1 = testNum;//test for new largest
	}

	// project polygon2
	min2 = axis.dotProduct(vectors2[0]);
	max2 = min2;//set 2's max and min
	
	for (j = 1; j < vectors2.length; j++) {
		testNum = axis.dotProduct(vectors2[j]);//project the point
		if (testNum < min2) min2 = testNum;//test for new min
		if (testNum > max2) max2 = testNum;//test for new max
	}

	// apply the offset to each max/min(no need for each point, max and min are all that matter)
	offset = axis.dotProduct(vectorOffset);//calculate offset
	min1 += offset;//apply offset
	max1 += offset;//apply offset
	
	// and test if they are touching
	test1 = min1 - max2;//test min1 and max2
	test2 = min2 - max1;//test min2 and max1
	if(test1 > 0 || test2 > 0){//if they are greater than 0, there is a gap
		return null;//just quit
	}
}
//if you're here, there is a collision
return new Vector2D(axis.x*((max2-min1)*-1), axis.y*((max2-min1)*-1)); //return the separation, apply it to a polygon to separate the two shapes.