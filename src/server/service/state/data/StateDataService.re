let getState = () => CreateStateDataService.stateData.state;

let setState = state => {
  CreateStateDataService.stateData.state = state;
  state;
};