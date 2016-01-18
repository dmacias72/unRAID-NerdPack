$(function(){
	sensorArray(false);
	eventArray();

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

	sensorRefresh();
});

//sensor refresh
function sensorRefresh() {
  sensorArray(true);
   setTimeout(sensorRefresh, 3000);
};

//load ipmi sensor table
function sensorArray(Refresh){
  	$.ajax({
      type: "POST",
      dataType: "json",
   	url: "/plugins/ipmitool-plugin/include/ipmitool_array.php",
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
   					if (parseFloat(Reading) < parseFloat(LowerNonRec) || parseFloat(Reading) > parseFloat(UpperNonRec))
   						Color = "red";
   					if (parseFloat(Reading) > parseFloat(LowerNonRec) && parseFloat(Reading) < parseFloat(UpperNonRec))
   						Color = "red";
   					if (parseFloat(Reading) > parseFloat(LowerCritical) && parseFloat(Reading) < parseFloat(UpperCritical))
   						Color = "orange";
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
						$("#tblSensor tbody")
						.append("<tr id='"+Name+"'>"+
						"<td title='"+data[i][3]+"'><img src='/plugins/ipmitool-plugin/images/green-on.png'/></td>"+ //status
						"<td>"+data[i][0]+"</td>"+ //sensor name
	   				"<td class='advanced'>"+ LowerNonRec   +"</td>"+
						"<td class='advanced'>"+ LowerCritical +"</td>"+
						"<td class='advanced'>"+ LowerNonCrit  +"</td>"+
						"<td class='reading "+ Color +"-text'>"+ Reading +"</td>"+ //sensor reading
						"<td>"+data[i][2]+"</td>"+ //sensor units
						"<td class='advanced'>"+ UpperNonCrit  +"</td>"+
						"<td class='advanced'>"+ UpperCritical +"</td>"+
						"<td class='advanced'>"+ UpperNonRec   +"</td>"+
						"</tr>");
					}
				}
   		});
		$("#tblSensor").trigger("update"); //update sensor table

		if ($.cookie('ipmitool_sensor_mode') == 'advanced')
			$('.advanced').show();
		else
			$('.advanced').hide();		 

		$('#tblSensor').tablesorter();
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
   	url: "/plugins/ipmitool-plugin/include/ipmitool_array.php",
   	data : {options: "-c sel elist" + Options + atob(Password)},
   	success: function(data) {
   		$.each(data, function (i, val) {
   			var Status = (data[i][5] == 'Asserted') ? 'red' : 'green';
 				$("#tblEvent tbody")
 				.append("<tr id='"+data[i][0]+"'>"+
				"<td title='"+data[i][5]+"'><img src='/plugins/ipmitool-plugin/images/" + Status + "-on.png'/></td>"+ //status 
				"<td>" + data[i][0] + "</td>"+ //event id
				"<td>" + data[i][1] + " "+data[i][2]+"</td>"+ //time stamp
				"<td>" + data[i][3] + "</td>"+ //sensor name
				"<td>" + data[i][4] +"</td>"+ //subject
				"<td><a class='delete'><i class='fa fa-trash' title='delete'></i></a>"+ //delete icon
				"</tr>");

				$('.delete').unbind('click').click(function () {
        			Delete($(this).parent().parent().attr("id"));
    			});
    			
   		});

			$("#tblEvent").trigger("update"); //update table for tablesorter

			$('#tblEvent').tablesorter({
				sortList: [[0,1]],
				widgets: ['saveSort', 'filter', 'stickyHeaders'],
				widgetOptions: {
					stickyHeaders_filteredToTop: true,
					filter_hideEmpty : true,
					filter_liveSearch : true,
					filter_saveFilters : true,
					filter_reset : 'a.reset',
					filter_functions: {
						'.filter-time' : {
			          	"3 days"   : function(e, n, f, i, $r, c, data) {
			          		return ($.now() - n <= 259200000); }, //3*24*60*60 3 days
   	  			    	"1 week"   : function(e, n, f, i, $r, c, data) {
   	  			    		return ($.now() - n <= 604800000); }, //7*24*60*60 1 week
	   		      	"2 weeks"  : function(e, n, f, i, $r, c, data) {
	   		      		return ($.now() - n <= 1209600000); }, //14*24*60*60 2 weeks
     				   	"1 month"  : function(e, n, f, i, $r, c, data) {
     				   		return ($.now() - n <= 2592000000); }, //30*24*60*60 1 month
     				   	"6 months" : function(e, n, f, i, $r, c, data) {
     				   		return ($.now() - n <= 15724800000); }, //26*7*24*60*60 6 months
     			   		"1 year"   : function(e, n, f, i, $r, c, data) {
     			   			return ($.now() - n <= 31449600000); } //52*7*24*60*60 1 year
	        			},
     				  	'.filter-name' : true
					}
				}
			})
			.tablesorterPager({
				container: $(".pager"),
				fixedHeight: false,
				size: 10
			});

			$("#allEvents").click(function() {
  				Delete('all');
			});

 		},
 		complete: function () {

 		},
       error : function() {}
	});
};

function Delete(Row) {
	var Confirm = (Row == "all") ? confirm("Are your sure you want to remove all events!?"): true;
	if (Confirm){
		var Method = (Row == "all") ? "clear " : "delete ";
		var EventId = (Row == "all") ? "" : Row;
		$.ajax({
			type : "POST",
			url : "/plugins/ipmitool-plugin/include/delete_event.php",
			data : {options: Method + EventId + Options + atob(Password)},
			success: function(data) {
				if (Row == "all")
					$("#tblEvent tbody").empty(); // empty table
				else
					$('#'+Row).remove(); //remove table row
				},
			error : function() { }
		});
	}
};
