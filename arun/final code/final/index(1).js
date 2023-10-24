function submitForm() {
    // event.preventDefault(); // Prevent the default form submission
  
    const inputs = document.getElementsByTagName('input'); // Get all input elements
  
    // Create an empty array to hold the data
    const data = [];
  
    // Loop through each input element
    for (let i = 0; i < inputs.length; i++) {
      const input = inputs[i];
      const id = input.id;
      const value = input.value;
  
      // Push an object with the column name (id) and value to the data array
      data.push({ [id]: value });
    }
  
    // Generate the Excel sheet
    const worksheet = XLSX.utils.json_to_sheet(data);
    const workbook = XLSX.utils.book_new();
    XLSX.utils.book_append_sheet(workbook, worksheet, 'Sheet1');
    const excelBuffer = XLSX.write(workbook, { bookType: 'xlsx', type: 'array' });
  
    // Save the Excel sheet as a file
    saveExcelFile(excelBuffer, 'registration.xlsx');
  }
  
  function saveExcelFile(buffer, fileName) {
    const blob = new Blob([buffer], { type: 'application/octet-stream' });
  
    // Check if the browser supports the 'download' attribute
    if (typeof navigator.msSaveBlob !== 'undefined') {
      // For IE and Edge
      navigator.msSaveBlob(blob, fileName);
    } else {
      // For other browsers
      const url = window.URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = fileName;
      a.style.display = 'none';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  }
  