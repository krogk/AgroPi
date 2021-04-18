$(document).ready(function(){
	$('#temperature-slider').jRange({
        from: -40.0,
        to: 125.0,
        step: 1,
        // scale: [-40.0,0.0,50.0,100.0,125.0],
        format: '%s',
        showLabels: true,
        snap: true,
        isRange : true
    });
    $('#humidity-slider').jRange({
        from: 0.0,
        to: 100.0,
        step: 1,
        // scale: [0.0,25.0,50.0,75.0,100.0],
        format: '%s',
        showLabels: true,
        snap: true,
        isRange : true
    });
    $('#light-slider').jRange({
        from: 0.0,
        to: 120000.0,
        step: 1,
        // scale: [0.0,30000.0,60000.0,120000.0],
        format: '%s',
        showLabels: true,
        snap: true,
        isRange : true
    });
    $('#ethanol-slider').jRange({
        from: 0.0,
        to: 80.0,
        step: 1,
        // scale: [0.0,20.0,40.0,60.0,80.0],
        format: '%s',
        showLabels: true,
        snap: true,
        isRange : true
    });
    $('#tvoc-slider').jRange({
        from: 0.0,
        to: 60000.0,
        step: 1,
        // scale: [0.0,10000.0,20000.0,30000.0,40000.0,50000.0],
        format: '%s',
        showLabels: true,
        snap: true,
        isRange : true
    });
    $('#eco2-slider').jRange({
        from: 0.0,
        to: 60000.0,
        step: 1,
        // scale: [0.0,10000.0,20000.0,30000.0,40000.0,50000.0],
        format: '%s',
        showLabels: true,
        snap: true,
        isRange : true
    });
    $('#h2-slider').jRange({
        from: 0.0,
        to: 80.0,
        step: 1,
        // scale: [0.0,20.0,40.0,60.0,80.0],
        format: '%s',
        showLabels: true,
        snap: true,
        isRange : true
    });

});



function update_control_values(){
	var temperature_val = $('#temperature-slider').val().split(',');
	var humidity_val = $('#humidity-slider').val().split(',');
	var light_intensity_val = $('#light-slider').val().split(',');
	var ethanol_val = $('#ethanol-slider').val().split(',');
    var tvoc_val = $('#tvoc-slider').val().split(',');
    var eco2_val = $('#eco2-slider').val().split(',');
    var h2_val = $('#h2-slider').val().split(',');
    var heating_toggle = $('#heating-toggle').prop('checked');
    var airflow_toggle = $('#airflow-toggle').prop('checked');
    var light_toggle = $('#lights-toggle').prop('checked');

    if (heating_toggle == true){
        heating_toggle = 1;
    }
    else{
        heating_toggle = 0;
    }

    if (airflow_toggle == true){
        airflow_toggle = 1;
    }
    else{
        airflow_toggle = 0;
    }

    if (light_toggle == true){
        light_toggle = 1;
    }
    else{
        light_toggle = 0;
    }


	form_data = {
        'min_temp': temperature_val[0],
        'max_temp': temperature_val[1],
        'min_humidity': humidity_val[0],
        'max_humidity': humidity_val[1],
        'min_light': light_intensity_val[0],
        'max_light': light_intensity_val[1],
        'min_ethanol': ethanol_val[0],
        'max_ethanol': ethanol_val[1],
        'min_tvoc': tvoc_val[0],
        'max_tvoc': tvoc_val[1],
        'min_eco2': eco2_val[0],
        'max_eco2': eco2_val[1],
        'min_h2': h2_val[0],
        'max_h2': h2_val[1],
        'heating_toggle': heating_toggle,
        'airflow_toggle': airflow_toggle,
        'light_toggle': light_toggle
    }
    // form_data = JSON.stringify(form_data);
    console.log(form_data);
    $('#update-control-button').attr('disabled', true);

    $.postFORM("/sensor/:80", form_data, function(data){
        console.log(data);
        $('#update-control-button').attr('disabled', false);
        if (data.code == "00") {
            notify_success("Values updated");
            // $('#update-control-button').attr('disabled', false);
        }
        else{
            notify_failure(data.msg);
        }
    });
}