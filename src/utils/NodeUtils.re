let rec deleteFile = (url, name) =>
  Node.Fs.existsSync(url) ?
    Node.Fs.readdirSync(url)
    |> Js.Array.forEach(file => {
         let currentPath = Node.Path.join2(url, file);

         NodeExtend.statSync(currentPath)##isDirectory() ?
           deleteFile(currentPath, name) :
           file |> Js.String.indexOf(name) > (-1) ?
             Node.Fs.unlinkSync(currentPath) : ();
       }) :
    ();

let rec deleteDirAllFile = url =>
  Node.Fs.existsSync(url) ?
    Node.Fs.readdirSync(url)
    |> Js.Array.forEach(file => {
         let currentPath = Node.Path.join2(url, file);

         NodeExtend.statSync(currentPath)##isDirectory() ?
           deleteDirAllFile(currentPath) : Node.Fs.unlinkSync(currentPath);
       }) :
    ();

let mkdirSyncIfNotExist = dirPath =>
  Node.Fs.existsSync(dirPath) ? () : NodeExtend.mkdirSync(dirPath);

let writeAllFileChunk = (filePath, chunkPath, (totalCount, hash)) => {
  for (x in 0 to totalCount - 1) {
    let fileChunkPath = {j|$chunkPath$hash-$x|j};

    let result = Node.Fs.readFileSync(fileChunkPath, `binary);

    NodeExtend.appendFileSync(filePath, result, "binary");
    Node.Fs.unlinkSync(fileChunkPath);
  };

  Node.Fs.rmdirSync(chunkPath);
};