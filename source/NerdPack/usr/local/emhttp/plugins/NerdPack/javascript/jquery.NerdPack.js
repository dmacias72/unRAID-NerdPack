$(function(){
	//tablesorter options
	$('#tblPackages').tablesorter({headers:{5:{sorter:false}}});

	// "uninstall package" switch and cookie
	$('#removepkg')
	.switchButton({
		labels_placement: "left",
		on_label: 'unInstall On',
  		off_label: 'unInstall Off',
  		checked: $.cookie('nerdpack_packages_remove') == 'remove'
  	})
	.change(function () {
		$.cookie('nerdpack_packages_remove', $('#removepkg').prop('checked') ? 'remove' : 'donotremove', { expires: 3650 });
	});

	// "delete package" switch and cookie
	$('#deletepkg')
	.switchButton({
		labels_placement: "left",
		on_label: 'delete On',
  		off_label: 'delete Off',
  		checked: $.cookie('nerdpack_packages_delete') == 'delete'
  	})
	.change(function () {
		$.cookie('nerdpack_packages_delete', $('#removepkg').prop('checked') ? 'delete' : 'donotdelete', { expires: 3650 });
	});

	// select all packages switch
	$('#checkall')
		.switchButton({
			labels_placement: "right",
			on_label: 'Select All',
			off_label: 'Select All',
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
	   success: function() {
			openBox('/plugins/NerdPack/scripts/packagemanager&arg1=download'+
						'&arg2='+$.cookie('nerdpack_packages_remove')+
						'&arg3='+$.cookie('nerdpack_packages_delete'),
						'Manage Packages',600,900,true);
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
			for( i in data ) {
				var Update;
				if (data[i].downloadeq == data[i].downloaded && data[i].installeq == data[i].installed )
					Update = "<span style=\"color:#44B012;white-space:nowrap;\"><i class=\"fa fa-check\"></i> up-to-date</span>";
				else
					Update = "<span style=\"white-space:nowrap;\"><i class=\"fa fa-cloud-download\"></i><a> update ready<a></span>";

				$("#tblPackages tbody").append(
				"<tr>"+
				"<td>"+data[i].name+"</td>"+ //package name
				"<td>"+Update+"</td>"+ //package status
				"<td>"+(data[i].size / 1000).toFixed(0)+"</td>"+ //package size
				"<td>"+data[i].downloaded+"</td>"+ //package installed
				"<td>"+data[i].installed+"</td>"+ //package installed
				"<td><input class='pkgcheckbox' id='"+data[i].pkgname+"' type='checkbox'>"+
				"<input class='pkgvalue' type='hidden' id='"+data[i].pkgname+"_value' name='"+
					data[i].pkgnver+"' value='"+data[i].config+"'></td>"+
				"</tr>");
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
