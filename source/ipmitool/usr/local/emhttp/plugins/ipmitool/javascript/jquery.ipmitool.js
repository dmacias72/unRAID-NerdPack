$(function(){
	sensorArray(false);
	eventArray();
	
	//bind Clear button to clearEvents function
	$("#btnClearEvents").bind("click", clearEvents);

	//advanced view switch
	$('.advancedview').switchButton({
		labels_placement: "left",
		on_label: 'Advanced View',
  		off_label: 'Basic View',
  		checked: $.cookie('ipmitool_sensor_mode') == 'advanced'
	});

	//set cookie and toggle advanced columns	
	$('.advancedview').change(function () {
		$('.advanced').toggle('slow');
		$.cookie('ipmitool_sensor_mode', $('.advancedview').prop('checked') ? 'advanced' : 'basic', { expires: 3650 });
	});
	
	$('#allEvents').click(function(event) {  //on click
   	if(this.checked) { // check select status
      	$('.checkEvent').each(function() { //loop through each checkbox
         	this.checked = true;  //select all checkboxes with class "checkEvent"              
         });
      }else{
         $('.checkEvent').each(function() { //loop through each checkbox
            this.checked = false; //deselect all checkboxes with class "checkEvent"                      
      	});        
      }
   });

	$('#tblSensor').tablesorter({headers:{0:{sorter:false}}});
	$('#tblEvent').tablesorter({headers:{0:{sorter:false}}});
	sensorRefresh();
});

function clearEvents() {
	//if all events checked clear all
	if($('#allEvents').prop('checked')) {
 		$('#allEvents').attr('checked', false);
    	$.ajax({
   		type : "POST",
 	  		url : "/plugins/ipmitool/include/delete_event.php",
    	 	data : {options: "clear" + Options + atob(Password)},
    	 	success: function(data) {
    	 		$("#tblEvent tbody").empty();
     		},
      	 error : function() { }
   	});
	} else {
	// clear only checked events
   $(':checkbox:checked').each(function(){
   	var EventId = $(this).val(); //get event id
  		var par = $(this).parent().parent(); //get table row
   	 	$.ajax({
  	   		type : "POST",
   	   	url : "/plugins/ipmitool/include/delete_event.php",
	      	data : {options: "delete " + EventId + Options + atob(Password)},
   	   	success: function(data) {
					par.remove(); //remove table row
       		},
	       error : function() { }
   		});
   	});
   }
};

//sensor refresh
(function sensorRefresh() {
  sensorArray(true);
   setTimeout(sensorRefresh, 30000);
}());

//load ipmi sensor table
function sensorArray(Refresh){
	var Display = 'none';

	if ($.cookie('ipmitool_sensor_mode') == 'advanced') {
		$('.advanced').show();
		Display = 'table-cell';
	} 
  	$.ajax({
      type: "POST",
      dataType: "json",
   	url: "/plugins/ipmitool/include/ipmitool_array.php",
   	data : {options: "-vc sdr" + Options + atob(Password)},
   	success: function(data) {
   		$.each(data, function (i, val) {
   			if (data[i][3] != "ns") {
   				var Reading = data[i][1];
   				var LowerNonRec = data[i][13];
   				var LowerCritical = data[i][14];
   				var LowerNonCrit = data[i][15];
   				var UpperNonCrit = data[i][12];
   				var UpperCritical = data[i][11];
   				var UpperNonRec = data[i][10];
   				var Color = "green";
					var Name = data[i][0].replace('+', 'plus_').replace('-', 'minus_').replace(' ', '_').replace('.', '_');
					
   				if (data[i][6]=="Voltage"){
   					if (parseFloat(Reading) > parseFloat(LowerNonRec) && parseFloat(Reading) < parseFloat(UpperNonRec))
   						Color = "red";
   					if (parseFloat(Reading) > parseFloat(LowerCritical) && parseFloat(Reading) < parseFloat(UpperCritical))
   						Color = "yellow";
   					if (parseFloat(Reading) > parseFloat(LowerNonCrit) && parseFloat(Reading) < parseFloat(UpperNonCrit))
   						Color = "green";
   				} else if (data[i][6]=="Fan"){
   					if (parseInt(Reading) < parseInt(LowerNonCrit))
   						Color = "red";
   				} else if (data[i][6]=="Temperature"){
   					if (parseInt(Reading) > parseInt(UpperNonCrit))
   						Color = "red";
   				}
   				
   				if (Refresh) {
						$("#" + Name + " td.reading").html("<font color='" + Color + "'>" + Reading + "</font>");
					} else {
						$("#tblSensor tbody").append(
						"<tr id='"+Name+"'>"+
						"<td title='"+data[i][3]+"'><img src='/plugins/ipmitool/images/green-on.png'/></td>"+ //status
						"<td>"+data[i][0]+"</td>"+ //sensor name
	   				"<td class='advanced' style='display:" + Display + ";'>" + LowerNonRec + "</td>"+
						"<td class='advanced' style='display:" + Display + ";'>" + LowerCritical + "</td>"+
						"<td class='advanced' style='display:" + Display + ";'>" + LowerNonCrit + "</td>"+
						"<td class='reading'>" + "<font color='" + Color + "'>" + Reading + "</font>" + "</td>"+ //sensor reading
						"<td>"+data[i][2]+"</td>"+ //sensor units
						"<td class='advanced' style='display:" + Display + ";'>" + UpperNonCrit + "</td>"+
						"<td class='advanced' style='display:" + Display + ";'>" + UpperCritical + "</td>"+
						"<td class='advanced' style='display:" + Display + ";'>" + UpperNonRec + "</td>"+
						"</tr>");
					}
				}
   		});
		$("#tblSensor").trigger("update"); //update sensor table for tablesorter
 		},
       error : function() {},
       cache: false
	});
};

//load ipmi event table
function eventArray(){
	$("#tblEvent tbody").empty();

  	$.ajax({
      type: "POST",
      dataType: "json",
   	url: "/plugins/ipmitool/include/ipmitool_array.php",
   	data : {options: "-c sel elist" + Options + atob(Password)},
   	success: function(data) {
   		$.each(data, function (i, val) {
   			var Status = (data[i][5] == 'Asserted') ? 'red' : 'green';
   			var Sensor = (data[i][3]).split(" "); // separate sensor name and type
				$("#tblEvent tbody").append(
				"<tr>"+
				"<td>	<input class='checkEvent' type='checkbox' value=" + data[i][0] + "></td>"+ //checkbox
				"<td title='"+data[i][5]+"'><img src='/plugins/ipmitool/images/" + Status + "-on.png'/></td>"+ //status 
				"<td>" + data[i][0] + "</td>"+ //event id
				"<td>" + data[i][1] + " "+data[i][2]+"</td>"+ //time stamp
				"<td>" + Sensor[1] + "</td>"+ //sensor name
				"<td>" + Sensor[0] + "</td>"+ //sensor type
				"<td>" + data[i][4] +"</td>"+ //subject
				"<td>" + data[i][6] + "</td>"+ //description
				"</tr>");
			$("#tblEvent").trigger("update"); //update table for tablesorter
     		});
 		},
       error : function() {}
	});
};