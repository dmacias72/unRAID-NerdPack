$(function(){
	// tablesorter options
	$("#tblPackages").tablesorter({
		sortList: [[0,0]],
		widgets: ["saveSort", "filter", "stickyHeaders"],
		widgetOptions: {
			stickyHeaders_filteredToTop: true,
			filter_hideEmpty: true,
			filter_liveSearch: true,
			filter_saveFilters: true,
			filter_reset: ".reset",
			filter_functions: {
				".filter-version": true,
				".filter-downloaded": true,
				".filter-installed": true
			}
		}
	});

	// "uninstall package" switch and cookie
	$("#uninstallpkg")
		.switchButton({
			labels_placement: "left",
			on_label: "unInstall On",
			off_label: "unInstall Off",
			checked: $.cookie("nerdpack_packages_uninstall") == "--uninstall"
		})
		.change(function () {
			$.cookie("nerdpack_packages_uninstall", $(this).prop("checked") ? "--uninstall" : "", { expires: 3650 });
		});

	// "delete package" switch and cookie
	$("#deletepkg")
		.switchButton({
			labels_placement: "left",
			on_label: "delete On",
			off_label: "delete Off",
			checked: $.cookie("nerdpack_packages_delete") == "--delete"
		})
		.change(function () {
			$.cookie("nerdpack_packages_delete", $(this).prop("checked") ? "--delete" : "", { expires: 3650 });
		});

	// select all packages switch
	$("#checkall")
		.switchButton({
			labels_placement: "right",
			on_label: "Select All",
			off_label: "Select All",
			checked: $.cookie("nerdpack_checkall") == "yes"
		})
		.change(function () {
			var myval = $(this).prop("checked");
			$.cookie("nerdpack_checkall", myval ? "yes" : "no", { expires: 3650 });
			$("#tblPackages tbody td:visible .pkgcheckbox").switchButton({checked: myval});
		});

	// set cookie on apply button press
	$("#btnApply").click(function() {
		checkDepends();

		$.ajax({
			type: "POST",
			url: "/update.php",
			data: $("#package_form").serializeArray(),
			success: function() {
				openBox("/plugins/NerdPack/scripts/packagemanager&arg1=--download"+
							"&arg2="+$.cookie("nerdpack_packages_uninstall")+
							"&arg3="+$.cookie("nerdpack_packages_delete"),
							"Package Manager", 600, 900, true);
			}
		});
	});

	packageQuery();
});

//list all available packages in a table
function packageQuery(force) {
	$("#tblPackages tbody").html("<tr><td colspan=\"6\"><br><i class=\"fa fa-spinner fa-spin icon\"></i><em>Please wait, retrieving plugin information ...</em></td><tr>");
	$.getJSON("/plugins/NerdPack/include/PackageQuery.php", {force: force}, function(data) {
		$("#tblPackages tbody").empty();
		for (var i in data) {
			var Update;
			if (data[i].downloadeq == data[i].downloaded && data[i].installeq == data[i].installed)
				Update = "<span style=\"color:#44B012;white-space:nowrap;\"><i class=\"fa fa-check\"></i> up-to-date</span>";
			else
				Update = "<span style=\"white-space:nowrap;\"><a><i class=\"fa fa-cloud-download\"></i> update ready</a></span>";

			var Downloaded = data[i].downloaded;
			if (data[i].downloadeq != data[i].downloaded)
				Downloaded = 'old';

			var Installed = data[i].installed;
			if (data[i].installeq != data[i].installed)
				Installed = 'old';

			$("#tblPackages tbody").append("<tr>"+
			"<td class='package' title='"+data[i].desc+"'>"+data[i].name+"</td>"+ // package name
			"<td>"+Update+"</td>"+ // package status
			"<td>"+data[i].size+"</td>"+ // package size
			"<td>"+Downloaded+"</td>"+ // package downloaded
			"<td>"+Installed+"</td>"+ // package installed
			"<td>"+data[i].plugins+"</td>"+ // package dependents
			"<td><input class='pkgcheckbox' id='"+data[i].pkgname+"' type='checkbox' "+(data[i].config=="yes"?"checked":"")+">"+
			"<input class='pkgvalue' type='hidden' id='"+data[i].pkgname+"_value' name='"+data[i].pkgnver+"' value='"+data[i].config+"'></td>"+
			"</tr>");
		}

		// attach switch buttons to every package checkbox all at once
		$(".pkgcheckbox")
			.switchButton({
				labels_placement: "right",
				on_label: "On",
				off_label: "Off"
			})
			.change(function() {
				$(this).parent().parent().find(".pkgvalue").val(this.checked ? "yes": "no");
				if (this.checked)
					checkDepends();
				$("#btnApply").prop("disabled", false);
			});

		// restore filters
		var lastSearch = $("#tblPackages")[0].config.lastSearch;
		$("#tblPackages").trigger("update");
		$("#tblPackages").trigger("search", [lastSearch]);
	});
}

function checkDepends() {
	if ($("#screen").prop("checked")) {
		$("#utempter").switchButton({checked: true});
		$("#utempter", ".pkgvalue").val("yes");
	}
	if ($("#iotop").prop("checked")) {
		$("#python").switchButton({checked: true});
		$("#python", ".pkgvalue").val("yes");
	}
}