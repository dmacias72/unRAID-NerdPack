$(function(){
	//Shadowbox.init({onClose:packageQuery});
	//tablesorter options
	$('#tblPackages').tablesorter({headers:{5:{sorter:false}}});

	// "uninstall package" switch and cookie
	$('#removepkg')
	.switchButton({
		labels_placement: "right",
		on_label: 'uninstall packages On',
  		off_label: 'uninstall packages Off',
  		checked: $.cookie('nerdpack_packages') == 'remove'
  	})
	.change(function () {
		$.cookie('nerdpack_packages', $('#removepkg').prop('checked') ? 'remove' : 'donotremove', { expires: 3650 });
	});

	// select all packages switch
	$('#checkall')
		.switchButton({
			labels_placement: "right",
			on_label: 'select all',
			off_label: ' select all',
			checked: $.cookie('nerdpack_checkall') == 'yes'
		})
		.change(function() {  //on change
			if(this.checked) { // check select status
				$('.pkgcheckbox').each(function() { //loop through each checkbox
      	   	$(this).switchButton({checked: true});
    	     	});
				$('.pkgvalue').each(function() { //loop through each value
					$(this).val('yes');
				});
   	   }else{
      	   $('.pkgcheckbox').each(function() { //loop through each checkbox
         	   $(this).switchButton({checked: false});
     	 		});
				$('.pkgvalue').each(function() { //loop through each value
					$(this).val('no');
				});
      	}
   	});

   // set cookie on apply button press
	$('#btnApply').click(function(event) {
		$.cookie('nerdpack_checkall', $('#checkall').prop('checked') ? 'yes' : 'no', { expires: 3650 });
		packageManager();
	});

	packageQuery();
});

function packageManager() {
	$.ajax({
		type : "POST",
		url : "/update.php",
      data : $('#package_form').serializeArray(),
	   complete: function() {
			openBox('/plugins/NerdPack/scripts/packagemanager&arg1=webgui&arg2='+$.cookie('nerdpack_packages'),'Manage Packages',600,900,true);
 	   }
   });
};

//list all available packages in a table
function packageQuery() {
	$("#tblPackages tbody").empty();
	$.ajax({
		type: "GET",
		dataType: "json",
		url: "/plugins/NerdPack/include/PackageQuery.php",
		success: function(data) {
			if (data.length > 1){
				for( i in data ) {
					$("#tblPackages tbody").append(
					"<tr>"+
					"<td>"+data[i].name+"</td>"+ //package name
					"<td></td>"+ //package status
					"<td>"+(data[i].size / 1000).toFixed(0)+"</td>"+ //package size
					"<td>"+data[i].downloaded+"</td>"+ //package installed
					"<td>"+data[i].installed+"</td>"+ //package installed
					"<td><input class='pkgcheckbox' id='"+data[i].pkgname+"' type='checkbox'>"+
					"<input class='pkgvalue' type='hidden' id='"+data[i].pkgname+"_value' name='"+data[i].pkgnver+"' value='"+data[i].config+"'>"+
					"</td></tr>");
					$('#'+data[i].pkgname)
						.switchButton({
							labels_placement: 'right',
							on_label: 'On',
  							off_label: 'Off',
	  						checked: data[i].config == "yes"
  					})
  						.change(function() {
  							var par = $(this).parent().parent();
  							if(this.checked) 
  								par.find('.pkgvalue').val("yes");
  							else
  								par.find('.pkgvalue').val("no");
  							$("#btnApply").prop("disabled", false);
  							checkDepends();
  					});
  				}
			}else {
				$("#tblPackages tbody").append(
				"<tr>"+
				"<td><input type='button' value='Download Packages' onclick='downloadPackages();'></td>"+
				"</tr>");

			}
		},
		complete : function () {
			$("#tblPackages").trigger("update");
			packageCheck()
		},
		error: function () {
		}
	});
};

// check github for newer package and report status
function packageCheck() {
	$.ajax({
  		type: "GET",
      url: "/boot/config/plugins/NerdPack/packages.json",
      dataType: "json",
      success: function(data) {
			$('#tblPackages tbody tr').each(function(row, tr) {
				var tblPackage = $(tr).children("td:nth-child(1)").html();
	      	var tblName = $(tr).children("td:nth-child(6)").find('.pkgcheckbox').attr("id");
        		for( i in data ) {
		      	var Package = data[i].name;
		      	var pkgNameArray = Package.split('-');
					var pkgName = pkgNameArray[0];
					if (pkgNameArray.length > 4){
						for( var ii = 1; ii < pkgNameArray.length-3; ii++ ) {
							pkgName = pkgName+"-"+pkgNameArray[ii];
						}
					}
					if ( tblName == pkgName){
						if (tblPackage == Package)
							var Update = "<span style=\"color:#44B012;white-space:nowrap;\"><i class=\"fa fa-check\"></i> up-to-date</span>";
						else
							var Update = "<span style=\"white-space:nowrap;\"><i class=\"fa fa-cloud-download\"></i><a href='#' onclick='packageUpdate(\""+tblName+"\",\""+tblPackage+"\",\""+Package+"\",\""+data[i].sha+"\");'> update ready<a></span>";
					}
				}
				$(tr).children("td:nth-child(2)").html(Update);
			});
			
		},
		complete : function () {
		$("#tblPackages").trigger("update");
		},
		error: function () {
		}
	});
};

// update packages
function packageUpdate(pkgName, pkgOld, pkgNew, pkgSha) {
	$.ajax({
		type: "POST",
		dataType: "json",
		url: "/plugins/NerdPack/include/PackageUpdate.php",
		data: {pkgname: pkgName, pkgold: pkgOld, pkgnew: pkgNew, pkgsha: pkgSha},
		success: function(data) {
			alert(data);
		},
		complete : function () {
			 //location.reload();
		},
		error: function () {
		}
	});
};

function downloadPackages() {
	$.ajax({
  		type: "POST",
      url: "/plugins/NerdPack/include/PackageDownload.php",
      dataType: "json",
      success: function(data) {
     			for( i in data ) {
					packageUpdate(null,null,data[i].name,data[i].sha);
				}
		},
		complete : function () {
		$("#tblPackages").trigger("update");
		},
		error: function () {
		}
	});
};


function checkDepends() {
	if ($('#screen').prop('checked') == true){
		$('#utempter').switchButton({checked: true});
		$('#utempter','.pkgvalue').val('yes');
	}
	if ($('#iotop').prop('checked') == true){
		$('#python').switchButton({checked: true});
		$('#python','.pkgvalue').val('yes');
	}
};
