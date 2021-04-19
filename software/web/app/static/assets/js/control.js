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

function update_temperature_value(){
    var temperature_val = $('#temperature-slider').val().split(',');

    temp_max = {'operation': 3, 'value': temperature_val[1]}
    temp_min = {'operation': 4, 'value': temperature_val[0]}

    post_data(temp_max);
    post_data(temp_min, true);
}

function update_humidity_value(){
    var humidity_val = $('#humidity-slider').val().split(',');

    hum_max = {'operation': 13, 'value': humidity_val[1]}
    hum_min = {'operation': 14, 'value': humidity_val[0]}

    post_data(hum_max);
    post_data(hum_min, true);
}

function update_light_value(){
    var light_intensity_val = $('#light-slider').val().split(',');

    light_max = {'operation': 1, 'value': light_intensity_val[1]}
    light_min = {'operation': 2, 'value': light_intensity_val[0]}

    post_data(light_max);
    post_data(light_min, true);
}

function update_ethanol_value(){
    var ethanol_val = $('#ethanol-slider').val().split(',');

    eth_max = {'operation': 9, 'value': ethanol_val[1]}
    eth_min = {'operation': 10, 'value': ethanol_val[0]}

    post_data(eth_max);
    post_data(eth_min, true);
}

function update_tvoc_value(){
    var tvoc_val = $('#tvoc-slider').val().split(',');

    tvoc_max = {'operation': 5, 'value': tvoc_val[1]}
    tvoc_min = {'operation': 6, 'value': tvoc_val[0]}

    post_data(tvoc_max);
    post_data(tvoc_min, true);
}

function update_eco2_value(){
    var eco2_val = $('#eco2-slider').val().split(',');

    eco2_max = {'operation': 7, 'value': eco2_val[1]}
    eco2_min = {'operation': 8, 'value': eco2_val[0]}

    post_data(eco2_max);
    post_data(eco2_min, true);
}

function update_h2_value(){
    var h2_val = $('#h2-slider').val().split(',');

    h2_max = {'operation': 11, 'value': h2_val[1]}
    h2_min = {'operation': 12, 'value': h2_val[0]}

    post_data(h2_max);
    post_data(h2_min, true);
}

function update_heating(){
    if ($('#heating-toggle').prop('checked')){
        heating = 1;
    }
    else{
        heating = 0;
    }

    if ($('#heating-heu-toggle').prop('checked')){
        heating_heu = 1;
    }
    else{
        heating_heu = 0;
    }

    heating = {'operation': 128, 'value': heating}
    heating_heu = {'operation': 132, 'value': heating_heu}

    post_data(heating);
    post_data(heating_heu, true);
}

function update_airflow(){
    if ($('#airflow-toggle').prop('checked')){
        airflow = 1;
    }
    else{
        airflow = 0;
    }

    if ($('#airflow-heu-toggle').prop('checked')){
        airflow_heu = 1;
    }
    else{
        airflow_heu = 0;
    }

    airflow = {'operation': 129, 'value': airflow}
    airflow_heu = {'operation': 133, 'value': airflow_heu}

    post_data(airflow);
    post_data(airflow_heu, true);
}

function update_lights(){
    if ($('#lights-toggle').prop('checked')){
        lights = 1;
    }
    else{
        lights = 0;
    }

    if ($('#lights-heu-toggle').prop('checked')){
        lights_heu = 1;
    }
    else{
        lights_heu = 0;
    }

    lights = {'operation': 130, 'value': lights}
    lights_heu = {'operation': 134, 'value': lights_heu}

    post_data(lights);
    post_data(lights_heu, true);
}

function update_water(){
    if ($('#water-toggle').prop('checked')){
        water = 1;
    }
    else{
        water = 0;
    }

    if ($('#water-heu-toggle').prop('checked')){
        water_heu = 1;
    }
    else{
        water_heu = 0;
    }

    water = {'operation': 131, 'value': water}
    water_heu = {'operation': 135, 'value': water_heu}

    post_data(water);
    post_data(water_heu, true);
}



// function update_control_values(){
// 	var temperature_val = $('#temperature-slider').val().split(',');
// 	var humidity_val = $('#humidity-slider').val().split(',');
// 	var light_intensity_val = $('#light-slider').val().split(',');
// 	var ethanol_val = $('#ethanol-slider').val().split(',');
//     var tvoc_val = $('#tvoc-slider').val().split(',');
//     var eco2_val = $('#eco2-slider').val().split(',');
//     var h2_val = $('#h2-slider').val().split(',');
//     var heating_toggle = $('#heating-toggle').prop('checked');
//     var airflow_toggle = $('#airflow-toggle').prop('checked');
//     var light_toggle = $('#lights-toggle').prop('checked');

//     if (heating_toggle == true){
//         heating_toggle = 1;
//     }
//     else{
//         heating_toggle = 0;
//     }

//     if (airflow_toggle == true){
//         airflow_toggle = 1;
//     }
//     else{
//         airflow_toggle = 0;
//     }

//     if (light_toggle == true){
//         light_toggle = 1;
//     }
//     else{
//         light_toggle = 0;
//     }

//     data_list = [
//         {'operation': 1, 'value': light_intensity_val[1]}, 
//         {'operation': 2, 'value': light_intensity_val[0]}, 
        
//         {'operation': 5, 'value': tvoc_val[1]}, 
//         {'operation': 6, 'value': tvoc_val[0]}, 
//         {'operation': 7, 'value': eco2_val[1]}, 
//         {'operation': 8, 'value': eco2_val[0]}, 
//         {'operation': 9, 'value': ethanol_val[1]}, 
//         {'operation': 10, 'value': ethanol_val[0]}, 
//         {'operation': 11, 'value': h2_val[1]}, 
//         {'operation': 12, 'value': h2_val[0]}, 
//         {'operation': 13, 'value': humidity_val[1]}, 
//         {'operation': 14, 'value': humidity_val[0]}, 
//         {'operation': 128, 'value': heating_toggle}, 
//         {'operation': 129, 'value': airflow_toggle}, 
//         {'operation': 130, 'value': light_toggle}, 
//     ]

// 	// form_data = {
//  //        'min_temp': temperature_val[0],
//  //        'max_temp': temperature_val[1],
//  //        'min_humidity': humidity_val[0],
//  //        'max_humidity': humidity_val[1],
//  //        'min_light': light_intensity_val[0],
//  //        'max_light': light_intensity_val[1],
//  //        'min_ethanol': ethanol_val[0],
//  //        'max_ethanol': ethanol_val[1],
//  //        'min_tvoc': tvoc_val[0],
//  //        'max_tvoc': tvoc_val[1],
//  //        'min_eco2': eco2_val[0],
//  //        'max_eco2': eco2_val[1],
//  //        'min_h2': h2_val[0],
//  //        'max_h2': h2_val[1],
//  //        'heating_toggle': heating_toggle,
//  //        'airflow_toggle': airflow_toggle,
//  //        'light_toggle': light_toggle
//  //    }
//     $('#update-control-button').attr('disabled', true);
//     // form_data = JSON.stringify(form_data);
//     console.log(form_data);
    
// }

function post_data(data_, notify){
    $.post("/sensor/:80", data_)
      .done(function( data ) {
        if(notify == true){
            notify_success("Values updated");
        }
    });

    // $.post("/sensor/:80", form_data, function( data ) {
    //     notify_success("Values updated");
    // });

    // $.postJSON("/sensor/:80", form_data, function(data){
    //     console.log(data);
    //     if (data.code == "00") {
    //         notify_success("Values updated");
    //     }
    //     else{
    //         notify_failure(data.msg);
    //     }
    //     $('#update-control-button').attr('disabled', false);
    // });
}






