open ApolloHooks;

module GetExchangeRates = [%graphql
  {|
  query getExchangeRates {
    rates(currency: "USD") {
      currency
      rate
    }
  }
|}
];

[@react.component]
let make = () => {
  let (simple, _full) = useQuery(GetExchangeRates.definition);

  <div>
    {switch (simple) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       //  let thingDivs =
       //    Array.map(thing => <div> {React.string(thing)} </div>, things);
       //  React.array(thingDivs);
       let currencies =
         switch (data##rates) {
         | Some(rates) =>
           // do something
           Array.map(
             rate =>
               switch (rate) {
               | Some(rate) =>
                 switch (rate##currency) {
                 | Some(currency) => <p> {React.string(currency)} </p>
                 | None => React.null
                 }
               | None => React.null
               },
             rates,
           )
         | None => [|React.null|]
         };
       React.array(currencies);
     | NoData
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
  </div>;
}