$(document).ready(function(){
    // init_chart_configs();
    init_temperature_chart();
    init_humidity_chart();
    init_light_intensity_chart();
    init_tvoc_chart();
    init_eco2_chart();
    init_ethanol_chart();
    init_h2_chart();
    // sending a connect request to the server.
    var socket = io.connect('http://localhost:5050');

    socket.on('after_connect', function(msg){
       console.log('After connect', msg);
    });


    socket.on('measurement_updated', function(data) {
        console.log('Measurement updated', data);
        
        if (data.type == "TEMPERATURE"){
          if (temperature_data.length > 20){
            temperature_data.shift();
          }
          temperature_data.push({'x': data.x, 'y': data.y})
          temperature_chart.updateSeries([{
            data: temperature_data
          }]);
          // console.log(temperature_data);
        }
        else if(data.type == "HUMIDITY"){
          if (humidity_data.length > 20){
            humidity_data.shift();
          }
          humidity_data.push({'x': data.x, 'y': data.y})
          humidity_chart.updateSeries([{
            data: humidity_data
          }]);
        }
        else if(data.type == "TVOC"){
          if (tvoc_data.length > 20){
            tvoc_data.shift();
          }
          tvoc_data.push({'x': data.x, 'y': data.y})
          tvoc_chart.updateSeries([{
            data: tvoc_data
          }]);
        }
        else if(data.type == "ECO2"){
          if (eco2_data.length > 20){
            eco2_data.shift();
          }
          eco2_data.push({'x': data.x, 'y': data.y})
          eco2_chart.updateSeries([{
            data: eco2_data
          }]);
        }
        else if(data.type == "ETHANOL"){
          if (ethanol_data.length > 20){
            ethanol_data.shift();
          }
          ethanol_data.push({'x': data.x, 'y': data.y})
          ethanol_chart.updateSeries([{
            data: ethanol_data
          }]);
        }
        else if(data.type == "H2"){
          if (h2_data.length > 20){
            h2_data.shift();
          }
          h2_data.push({'x': data.x, 'y': data.y})
          h2_chart.updateSeries([{
            data: h2_data
          }]);
        }
        else if(data.type == "LIGHT_INTENSITY"){
          if (light_intensity_data.length > 20){
            light_intensity_data.shift();
          }
          light_intensity_data.push({'x': data.x, 'y': data.y})
          light_intensity_chart.updateSeries([{
            data: light_intensity_data
          }]);
        }
    });
});




var time_series_chart = null;
var temperature_chart = null;
var humidity_chart = null;
var tvoc_chart = null;
var eco2_chart = null;
var ethanol_chart = null;
var h2_chart = null;
var light_intensity_chart = null;

var temperature_data = [];
var humidity_data = [];
var tvoc_data = [];
var eco2_data = [];
var ethanol_data = [];
var h2_data = [];
var light_intensity_data = [];

function get_dashboard_data(){
    var start_date = $('.date-range').data('daterangepicker').startDate._d;
    var end_date = $('.date-range').data('daterangepicker').endDate._d;

    var now = moment();

    if (start_date != ""){
        start_date = $.date(start_date);
    }
    else{
        start_date = $.date(now.startOf('hour').subtract(5, 'hour'));
    }

    if (end_date != ""){
        end_date = $.date(end_date);
    }
    else{
        end_date = $.date(now.startOf('hour'));
    }

    form_data = {
        'start_date': start_date,
        'end_date': end_date
    }
    form_data = JSON.stringify(form_data);
    console.log(form_data);
    $.postJSON("/dashboard", form_data, function(data){
        console.log(data);
        if (data.code == "00") {
            temperature_chart.updateSeries([{
              data: data.data.temperature
            }]);

            humidity_chart.updateSeries([{
              data: data.data.humidity
            }]);

            tvoc_chart.updateSeries([{
              data: data.data.tvoc
            }]);

            eco2_chart.updateSeries([{
              data: data.data.eco2
            }]);

            ethanol_chart.updateSeries([{
              data: data.data.ethanol
            }]);

            h2_chart.updateSeries([{
              data: data.data.h2
            }]);
            // display_time_series_chart(count_data.legal_aid_chart, count_data.firm_requests_chart);
        }
        else{
            notify_failure("Error", data.msg);
        }
    });
}

function init_temperature_chart(){
  var options = {
    series: [{
      name: "Temperature",
      data: temperature_data
    }],
      chart: {
      height: 350,
      id: 'realtime',
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'Temperature',
      align: 'left'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: [],
      range: 10
    }
  };

  temperature_chart = new ApexCharts(document.querySelector("#temperature-chart"), options);
  temperature_chart.render();
}

function init_humidity_chart(){
  var options = {
    series: [{
      name: "Humidity",
      data: humidity_data
    }],
      chart: {
      height: 350,
      id: 'realtime',
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'Humidity',
      align: 'left'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: [],
      range: 10
    }
  };

  humidity_chart = new ApexCharts(document.querySelector("#humidity-chart"), options);
  humidity_chart.render();
}

function init_light_intensity_chart(){
  var options = {
    series: [{
      name: "Light Intensity",
      data: light_intensity_data
    }],
      chart: {
      height: 350,
      id: 'realtime',
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'Light Intensity',
      align: 'left'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: [],
      range: 10
    }
  };

  light_intensity_chart = new ApexCharts(document.querySelector("#light-intensity-chart"), options);
  light_intensity_chart.render();
}

function init_tvoc_chart(){
  var options = {
    series: [{
      name: "TVOC",
      data: tvoc_data
    }],
      chart: {
      height: 350,
      id: 'realtime',
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'TVOC',
      align: 'left'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: [],
      range: 10
    }
  };

  tvoc_chart = new ApexCharts(document.querySelector("#tvoc-chart"), options);
  tvoc_chart.render();
}

function init_eco2_chart(){
  var options = {
    series: [{
      name: "ECO2",
      data: eco2_data
    }],
      chart: {
      height: 350,
      id: 'realtime',
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'ECO2',
      align: 'left'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: [],
      range: 10
    }
  };

  eco2_chart = new ApexCharts(document.querySelector("#eco2-chart"), options);
  eco2_chart.render();
}

function init_ethanol_chart(){
  var options = {
    series: [{
      name: "Ethanol",
      data: ethanol_data
    }],
      chart: {
      height: 350,
      id: 'realtime',
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'Ethanol',
      align: 'left'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: [],
      range: 10
    }
  };

  ethanol_chart = new ApexCharts(document.querySelector("#ethanol-chart"), options);
  ethanol_chart.render();
}

function init_h2_chart(){
  var options = {
    series: [{
      name: "H2",
      data: h2_data
    }],
      chart: {
      height: 350,
      id: 'realtime',
      type: 'line',
      zoom: {
        enabled: false
      }
    },
    dataLabels: {
      enabled: false
    },
    stroke: {
      curve: 'straight'
    },
    title: {
      text: 'H2',
      align: 'left'
    },
    grid: {
      row: {
        colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
        opacity: 0.5
      },
    },
    xaxis: {
      categories: [],
      range: 10
    }
  };

  h2_chart = new ApexCharts(document.querySelector("#h2-chart"), options);
  h2_chart.render();
}


