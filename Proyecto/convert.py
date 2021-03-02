import os

try:
    import PyPDF2 as pdf
    print("Convirtiendo el archivo PDF a TXT...")
except ImportError:
    print("Instalando el modulo para leer el PDF")
    os.system("pip install PyPDF2")
    import PyPDF2 as pdf
    print("Convirtiendo el archivo PDF a TXT...")
    
cedulasInt = []
pdfFileObj = open('Cedulas.pdf', 'rb')
pdfReader = pdf.PdfFileReader(pdfFileObj) 
for i in range(pdfReader.numPages):
    pageObj = pdfReader.getPage(i)
    text = pageObj.extractText()
    text = text.split("\n")
    for j in text:
        try:
            cedInt = int(j)
            cedulasInt.append(cedInt)
        except ValueError:
            pass
pdfFileObj.close()

fTXT = open("Cedulas.txt", "w")
for i in cedulasInt:
    fTXT.write(str(i)+"\n")
fTXT.write("f")
fTXT.close()
print("Archivo 'Cedulas.txt' generado, con los numeros de cedula para usarse en los códigos en C")