$(function() {
  $( "#datepicker-3" ).datepicker({
    //appendText:"(yy-mm-dd)",
    dateFormat:"d/m/y",
    //altField: "#datepicker-4",
    //altFormat: "DD, d MM, yy"
  });
});

var date = " ";
document.getElementById("submitBtn").addEventListener("click", everythingelse);

function everythingelse()
{
  d3.selectAll("svg > *").remove();
  var date = "";
  var d = document.getElementById("datepicker-3").value;
  date = d;
  //document.getElementById("datepicker-4").value = "" + date;

  // Parse the date / time
  var parseTime = d3.timeParse("%H:%M");
  //var parseTime = d3.timeParse("%d-%b-%y");

  // Reads the file/Gets the data
  d3.tsv("dates.txt", function(d)
  {
    var filtered;

    //d.date = d.date;
    //d.temp = d.temp;
    //d.time = d.time;

    console.log("selected date: " + date);
    console.log("time: " + d.time);
    console.log("date: " + d.date);
    console.log("temp: " + d.temp);

    // Checks if the input date matches the file's dates
    if (d.date == date)
    {
      filtered = d;
      console.log("d.date: " + d.date);
      console.log("date: " + date);
    }

    return filtered;
    //return d;

  }, function(error, data)
  {
    if (error) throw error;


    // Format the data
    data.forEach(function(d)
    {
      d.time = parseTime(d.time);
      d.temp = +d.temp;
    });

    //console.log("debug all: " + data);
    //console.log("debug time: " + data.time);
    //console.log("debug date: " + data.date);
    //console.log("debug temp: " + data.temp);

    // Set the dimensions and margins of the graph
    // Append the svg obgect to the body of the page
    // Appends a 'group' element to 'svg'
    // Moves the 'group' element to the top left margin
    var svg = d3.select("svg"),
    margin = {top: 20, right: 20, bottom: 30, left: 50},
    width = +svg.attr("width") - margin.left - margin.right,
    height = +svg.attr("height") - margin.top - margin.bottom,
    g = svg.append("g").attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    // Set the ranges
    var x = d3.scaleTime().rangeRound([0, width]);
    var y = d3.scaleLinear().rangeRound([height, 0]);

    // Define the line
    var line = d3.line()
    .x(function(d) { return x(d.time); })
    .y(function(d) { return y(d.temp); });

    // Scale the range of the data
    x.domain(d3.extent(data, function(d) { return d.time; }));
    y.domain(d3.extent(data, function(d) { return d.temp; }));

    // Select the section we want to apply our changes to
    //var svg = d3.select("g").transition();

    // Add the X Axis
    g.append("g")
    .attr("class", "axis axis--x")
    .attr("transform", "translate(0," + height + ")")
    .call(d3.axisBottom(x))
    .append("text")
    .attr("fill", "#000")
    .attr("y", 30)
    .attr("x", 430)
    .style("text-anchor", "middle")
    .text("Time");
    // Add the Y Axis
    g.append("g")
    .attr("class", "axis axis--y")
    .call(d3.axisLeft(y))
    .append("text")
    .attr("fill", "#000")
    .attr("transform", "rotate(-90)")
    .attr("y", 6)
    .attr("dy", "0.71em")
    .style("text-anchor", "end")
    .text("Temperature (C)");

    // Add the valueline path.
    g.append("path")
    .datum(data)
    //.data(data)
    .attr("class", "line")
    .attr("d", line);
  });
}
